#!/bin/bash
clear
n=$1
nivel=$(echo 2^$n | bc)
./binario $n &
pid_padre=$(pgrep binario | head -n 1 ) #Obtenemos el pid del primer proceso creado
echo "$pid_padre"
#Comando para comprobar la poda en el arbol
ps -eo pid,comm | grep binario | head -n 1 | awk {'print $1'} | xargs pstree -c

hijo_izquierdo=$(ps --ppid $pid_padre | sed -n '2p' | awk {'print $1'} )
hijo_derecho=$(ps --ppid $pid_padre | sed -n '3p'| awk {'print $1'} )

echo "Hijo izquierdo $hijo_izquierdo"
echo "Hijo derecho $hijo_derecho"

echo ""
i=1 #Indice utilizado para rellenar el arreglo de hijos y padres



arreglo[0]="$pid_padre"
arreglo[1]="$hijo_izquierdo"
arreglo[2]="$hijo_derecho"

echo ${arreglo[@]} #Comprobar el arreglo 

#Variables que se utilizan para llenar el arreglo
x1=2
x2=3
#-------------------------------------------------

#Comienza llenado de arreglos
if [ $n -gt 2 ] 
then
    for((i=1;i<=$nivel/2;i++))
    do
        if [ $i -eq 1 ]
        then
            h_izq_pos=$(($i+$x1))
            h_der_pos=$(($i+$x2))
            echo "Valor de h izq pos=$h_izq_pos en if"
            echo "Valor de h der pos=$h_der_pos"
            arreglo[$h_izq_pos]=$(ps --ppid ${arreglo[i]} | sed -n '2p' | awk {'print $1'})
            arreglo[$h_der_pos]=$(ps --ppid ${arreglo[i]} | sed -n '3p' | awk {'print $1'})
            
        else
            x1=$(($x2))
            x2=$(($x2+1))
            h_izq_pos=$(($i+$x1))
            h_der_pos=$(($i+$x2))
            echo "Valor de h izq pos=$h_izq_pos en else"
            echo "Valor de h der pos=$h_der_pos"
            arreglo[$h_izq_pos]=$(ps --ppid ${arreglo[i]} | sed -n '2p' | awk {'print $1'})
            arreglo[$h_der_pos]=$(ps --ppid ${arreglo[i]} | sed -n '3p' | awk {'print $1'})
        fi
    
    done
 fi   

 
 echo "Arreglo llenado"
echo ${arreglo[@]} #Comprobar el arreglo     
    
killall binario
#pstree -aps | grep binario
