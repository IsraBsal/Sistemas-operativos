#!/bin/bash
n=$1 #Hijos que le pasamos

#Número total de procesos que hay
numTotalPadres=$(ps -ef --no-headers | wc -l)

#Contador de procesos
proceso_con_n_hijos=0

for(( i=1;i<numTotalPadres;i++ ))
do
    j=$(($i+1)) #j es utilizado para moverme entre el numero de pid del cual quiero saber cuantos hijos tiene
    #Proceso contiene el pid
    proceso=$(ps -eo ppid --sort ppid --no-headers | sed -n ''$j'p') #El comando nos tira una linea donde esta el pid, el $jp nos da pid por pid
    if [ $proceso -gt 0 ] #Saltamos el proceso 0 y el encabezado
    then
      #Numero de procesos que tiene un proceso padre
      numHijos=$(ps --ppid $proceso | wc -l)
      if [ $numHijos == $n ]
      then
          proceso_con_n_hijos=$(($proceso_con_n_hijos + 1))
      fi
    fi
done
echo "Procesos con $n hijos: $proceso_con_n_hijos"
