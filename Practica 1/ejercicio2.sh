#!/bin/bash
procesos=$(ps -Ao comm --sort=-pcpu | head -n 6)
echo "$procesos"
