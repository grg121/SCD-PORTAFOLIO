#!/bin/bash

if [ $# != 1 ] 
then echo "número incorrecto de argumentos. Uso: ./ejecutar.sh <muestras> "
else
# AUMENTAR EL NÚMERO DE PRUEBAS 
	for h in `seq 1 100` 
	do
		for i in `seq 1 20`
		do
			echo $i `bin/calculopi $i $1 -pc  ` >> salida
    		done
	done

	gnuplot -e "set terminal png size 1300, 900 ; 
	set title 'Tiempo de ejecución - Número de hebras';
        set output 'grafico1.png' ; plot [0:10.5] 'salida' with points pointtype 3  " 
	gnuplot -e "set terminal png size 1300, 900 ; 
	set title 'Tiempo de ejecución - Número de hebras';
        set output 'grafico2.png' ; plot [0:20.5] 'salida' with points pointtype 3  " 
fi 
