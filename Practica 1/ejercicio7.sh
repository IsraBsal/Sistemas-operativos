#!/bin/bash

tiempo=$1
mail=$2

num_total_procesos=$(ps -ef --no-headers | wc -l)
#echo "$num_total_procesos"
anterior=0

#CReacion y encabezado del archivo
echo "proceson con mas de 5 hijos: " > bitacora

#Comienza logica

while [ true ]
do
  for((i=1;i<num_total_procesos;i++))
  do
    j=$(($i+1)) #j es utilizado para moverme entre el numero de pid del cual quiero saber cuantos hijos tiene
    #Proceso contiene el pid
    proceso=$(ps -eo ppid --sort ppid --no-headers | sed -n ''$j'p') #El comando nos tira una linea donde esta el pid, el $jp nos da pid por pid
    #echo "$proceso"
    if [ $proceso -eq $anterior ]
    then
      echo "salto"
    else
      if [ $proceso -gt 0 ] #Saltamos el proceso 0 y el encabezado
      then
        #Numero de procesos que tiene un proceso padre
        numHijos=$(ps --ppid $proceso | wc -l)

        if [ $numHijos -gt 5 ]
        then
            #echo $(ps --ppid $proceso) >> bitacora
            echo "proceso padre: $proceso" >> bitacora
            echo $(ps --ppid $proceso | tee >> bitacora)
            echo ""
            echo "Soy el papa $proceso y estos son mis hijos \t"
        fi
      fi
      anterior="${proceso}"

    fi

  done
  #mail -s “Correo” israellinux19@gmail.com -A bitacora
sleep $tiempo
done
