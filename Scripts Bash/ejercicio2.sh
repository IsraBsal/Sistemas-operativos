#!/bin/bash
#echo "$1"
procesos=$(ps -U $1 -u $1 -o user,comm,%cpu --sort=-pcpu | head -n 6) #user
echo "$procesos"
