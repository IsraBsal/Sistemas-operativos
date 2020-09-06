#!/bin/bash
n=$1 #Es el numero que nos dan en la llamada y $1 jala el numero
#Inicia la logica

#Obtenemos el total de los padres para delimitar
num_total_padres=$(ps -ef --sort ppid --no-headers | wc -l)
for (( i=0;i<=num_total_padres;i++ ))
do
  num_hijos=$(ps --ppid $i | wc -l)-1



done
