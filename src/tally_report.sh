#!/bin/bash

./genfinal.py  > final.csv

for target in $TARGETS; do 
  (cd $target; make; make stats)
  cat $target/final.csv >> final.csv
done

echo Done!
