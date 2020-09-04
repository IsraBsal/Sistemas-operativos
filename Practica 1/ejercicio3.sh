#!/bin/bash
echo "$1"

procesos=$(ps -U $1 -u $1 -o comm,%cpu | head -n 11) #user
echo "$procesos"
