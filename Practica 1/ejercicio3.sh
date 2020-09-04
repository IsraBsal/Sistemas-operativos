#!/bin/bash/
procesos=$(ps -Ao user,comm,pcpu --sort=-pcpu | head -n 11)
echo "$procesos"
