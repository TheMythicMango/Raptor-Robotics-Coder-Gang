#!/bin/bash
pros mu #builds the PROS project and uploads it to the brain

# runs the graphing program and puts data sent from the vex 
# brain into the text file at the same time
python3 CG/display.py & pros t | tee ./CG/data.txt 