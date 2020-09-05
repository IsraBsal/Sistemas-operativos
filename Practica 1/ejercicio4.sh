#!/bin/bash

echo "Introduce una password"
read -rs contra

if [ ${#contra} -ge  8 ];
then
        echo "Cumple con la longitud"
else
        echo "NO cumple con la longitud"
fi

contra_temp="${contra}"
echo "Contra temporal $contra_temp"
#Quitamos un numero
contra_temp=${contra_temp//[0-9]/}
#inicia logica
if [ ${#contra_temp} != ${#contra} ];
then
  contra_temp_signo=${contra_temp//[#@%&"+""-""*""="]/}
  if [ ${#contra_temp_signo} != ${#contra_temp} ];

  then
    echo "Password aceptada"
  else
    echo "Password no aceptada, falta especial"
  fi

else
  echo "Password no aceptada, falta numero"

fi
