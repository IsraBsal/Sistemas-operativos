#!bin/bash/

echo "Introduce una password"
read -r contra

if [ ${#contra} -ge  8 ];
then
        echo "Cumple con la longitud"
else
        echo "NO cumple con la longitud"
fi

contra_temp=${contra}
echo "Contra temporal $contra_temp"

num_verificacion= $contra | awk '/[a-z0-9@#$%&*-+=]/'

echo "$num_verificacion"


