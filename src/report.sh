#!/bin/bash
# requires TARGETS THIS

mkdir workdir 2> /dev/null


for program in $TARGETS; do
  ../genfinal.py $program
done

cat workdir/*.csv > final.csv


