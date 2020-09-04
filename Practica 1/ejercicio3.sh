#!/bin/bash
procesos=$(ps -Ao user,comm,%cpu --sort=-pcpu | head -n 11)
echo "$procesos"
