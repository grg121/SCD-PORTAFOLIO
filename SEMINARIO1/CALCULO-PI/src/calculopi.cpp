// *********************************************************************
// SCD. Ejemplos del seminario 1.
//
// Plantilla para el ejercicio de cálculo de PI
// *********************************************************************

#include <iostream>
#include <pthread.h>
#include <fun_tiempo.h>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* strtoul */
#include <sstream>


using namespace std ;

// ---------------------------------------------------------------------
// constante y variables globales (compartidas entre hebras)

unsigned long long m = 1;

const unsigned long m0 =   long(1024) * long(1024) ;  // número de muestras (un millón)
unsigned n      = 4 ;                      // número de hebras

double * resultado_parcial ; // tabla de sumas parciales (una por hebra)

// ---------------------------------------------------------------------
// implementa función $f$

double f( double x )       
{ 
   return 4.0/(1+x*x) ;     // $~~~~f(x)\,=\,4/(1+x^2)$
}
// ---------------------------------------------------------------------
// cálculo secuencial

double calcular_integral_secuencial( )
{
   double suma = 0.0 ;                      // inicializar suma
   for( unsigned long i = 0 ; i < m ; i++ ) // para cada $i$ entre $0$ y $m-1$
      suma += f( (i+0.5)/m );               // $~~~~~$ añadir $f(x_i)$ a la suma actual
   return suma/m ;                          // devolver valor promedio de $f$
}
// ---------------------------------------------------------------------
// función que ejecuta cada hebra

void * funcion_hebra( void * ih_void ) 
{  
   unsigned long ih = (unsigned long) ih_void ; // número o índice de esta hebra
   double sumap = 0.0 ;

   for( unsigned long i = ih ; i < m ; i += n)
     sumap += f( (i+0.5)/m) ;
   
   resultado_parcial[ih] = sumap ; // guardar suma parcial en vector.
   return NULL ;
}
// ---------------------------------------------------------------------
// cálculo concurrente

double calcular_integral_concurrente( )
{
  double resultado_final = 0 ;
   // crear y lanzar $n$ hebras, cada una ejecuta "funcion\_concurrente"

  pthread_t * id_hebra = new pthread_t[n] ;

  for(unsigned long i = 0 ; i < n ; i++){
    void * arg_ptr = (void *) i ; 
    pthread_create(&(id_hebra[i]),NULL,funcion_hebra,arg_ptr) ;
  }
  
   // esperar (join) a que termine cada hebra, sumar su resultado

  for(unsigned i = 0 ; i < n ; i++)
    pthread_join( id_hebra[i], NULL) ;
  for(unsigned  i = 0 ; i < n ; i++)
    resultado_final += resultado_parcial[i] ;

  resultado_final /= m ;
  
   // devolver resultado completo

  delete id_hebra  ;
  
  return resultado_final ; 
}

// ---------------------------------------------------------------------

 int main(int argc, char *argv[]){

   if(argc != 3 && argc != 4){
    cout <<  endl 
	 << "NUMERO DE ARGUMENTOS INCORRECTO" << endl 
         << "Uso: ./calculopi n m, donde n = número de hebras, m = número de muestras (millones) "
	 << endl ;
  }
  else {


    

    stringstream strValue;

 strValue << argv[1] ;

 strValue >> n ;

 strValue << argv[2] ;

 strValue >> m ;

 m = m * m0 ;

    

    resultado_parcial = new double[n] ; 

    // cout << "Ejemplo 4 (cálculo de PI)" << endl ;
   double pi_sec = 0.0, pi_conc = 0.0 ;
   double tiempo_sec, tiempo_conc ; 

   struct timespec inicio_sec = ahora() ; 
   
   pi_sec = calcular_integral_secuencial() ;

   struct timespec fin_sec = ahora() ;

   tiempo_sec = duracion( &inicio_sec, &fin_sec) ;

   struct timespec inicio_conc = ahora() ; 
   
   pi_conc = calcular_integral_concurrente() ;

   struct timespec fin_conc = ahora() ;

   tiempo_conc = duracion(&inicio_conc, &fin_conc) ; 

   if(argc == 3) {
    
   cout << "valor de PI (calculado secuencialmente)  == " << pi_sec  << endl 
        << "valor de PI (calculado concurrentemente) == " << pi_conc << endl ;

   
   cout << "Tiempo de ejecución (secuencial)  == " << tiempo_sec << endl 
        << "Tiempo de ejecución (concurrente) == " << tiempo_conc << endl;

   double diferencia = tiempo_sec - tiempo_conc ;

   cout << "Diferencia: " << diferencia << endl ;

   } else {

     string opcion = argv[3] ;

     if(opcion == "-pc")
       cout << tiempo_conc << endl ; 
    
     else if(opcion == "-ps")
	 cout << tiempo_sec << endl ;
     else cout << "OPCION NO VÁLIDA" ; 

   }
   delete [] resultado_parcial ; 

   return 0 ; 
}
}
