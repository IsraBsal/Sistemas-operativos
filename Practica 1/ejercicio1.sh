#!/bin/bash
mem=$(grep MemTotal /proc/meminfo | awk {'print $2/1024/1024'})
echo "Memoria= $mem"
cpu=$(grep processor /proc/cpuinfo | wc -l)
echo "Nucleos del CPU= $cpu"

