#!/bin/bash

CHECKEDCCLANG=~/checkedc/checkedc-clang/llvm/cmake-build-debug/bin/clang
TARGETS="em3d mst treeadd bh perimeter tsp bisort health power voronoi"

for T in $TARGETS; do
  cd $T
  echo ===== $T =====
  make clean > /dev/null 2>&1
  echo == Making $T with Checked C
  make CC=$CHECKEDCCLANG > /dev/null 2>&1
  echo == Reverting $T, building result
  make ${T}_c3 > /dev/null 2>&1
  echo == Testing
  make test > /dev/null 2>&1
  cd ..
done
