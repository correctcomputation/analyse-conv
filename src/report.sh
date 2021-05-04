#!/bin/bash
# requires TARGETS THIS
# Run genfinal in each target
# and then cat each generated table 
# into a "final" table

mkdir workdir 2> /dev/null


for program in $TARGETS; do
  ../genfinal.py $program
done

cat workdir/*.csv > final.csv


