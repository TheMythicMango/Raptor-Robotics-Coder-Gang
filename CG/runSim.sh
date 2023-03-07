#!/bin/bash

# runs the graphing program and puts data sent from the vex 
# brain into the text file at the same time
g++ -Wall -Wextra -I src -I include ./src/simMain.cpp
python3 CG/display.py & ./a.out