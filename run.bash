#!/bin/bash
 echo "Width = $(tput cols) Height = $(tput lines)"
LINES=$(tput lines)
COLUMNS=$(tput cols)
gcc -ansi -o main main.c -lm
./main $LINES $COLUMNS
