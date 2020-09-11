#!/bin/bash
clear
n=$1
./binario $n &
pid_padre=$(pgrep binario | head -n 1 ) #Obtenemos el pid del primer proceso creado
echo "$pid_padre"
#Comando para comprobar la poda en el arbol
ps -eo pid,comm | grep binario | head -n 1 | awk {'print $1'} | xargs pstree -c

hijo_izquiero=$(ps --ppid $pid_padre | sed -n '2p' | awk {'print $1'} )
hijo_derecho=$(ps --ppid $pid_padre | sed -n '3p'| awk {'print $1'} )

echo "Hijo izquiero $hijo_izquiero"
echo "Hijo derecho $hijo_derecho"

i=1 #Indice utilizado para rellenar el arreglo de hijos y padres
killall binario

#pstree -aps | grep binario
