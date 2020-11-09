#!/bin/bash
#procesos_cpu=$(ps -Ao user,comm,%cpu --sort=-pcpu | head -n 11)
procesos_memoria=$(ps axo comm,pmem --sort -pmem | head -n 25)
echo "$procesos_memoria"
