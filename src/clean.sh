#!/bin/bash

for target in $TARGETS; do 
  (cd $target && make clean)
done
