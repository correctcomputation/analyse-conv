#!/bin/bash

# Grab our headers
./genfinal.py  > final.csv

# Loop through targets and start 
# append their final result to the global final
for target in $TARGETS; do 
  (cd $target && make && make stats)
  cat $target/final.csv >> final.csv
done

echo Done!
