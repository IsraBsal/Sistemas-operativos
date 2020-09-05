#!/bin/bash
clear
ps -eo comm,thcount --sort -thcount | sed -n  | awk '{print "El proceso con mas hilos es: "$1" y tiene "$2" hilos "}'
