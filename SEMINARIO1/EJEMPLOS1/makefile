all: calculopi

calculopi: calculopi.o fun_tiempo.o 
	g++ -o calculopi calculopi.o fun_tiempo.o -lrt -lpthread

calculopi.o: calculopi.cpp
	g++ -g -c calculopi.cpp
fun_tiempo.o: fun_tiempo.c
	gcc -g -c fun_tiempo.c


