#!/bin/bash

if [ $# -ne 2 ]
then 
echo "El número correcto de parámetros es 2: <hebras> <c/s> " 
     
elif [ "$2" == "c" ] then
	for h in `seq 1 100` 
	do
		for i in `seq 1 10`
		do
			echo $i `bin/calculopi $1 $i -pc` >> salida 
    		done
	done
fi

	                               
