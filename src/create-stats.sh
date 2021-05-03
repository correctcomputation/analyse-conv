#!/bin/bash
# Computes statistics about the diffs between various versions of a target

# Rationale for these diff pairs:
# (1) orig --> revert: This is the refactoring work
# (2) revert --> manual: This is the annotation work
# (3) revert --> 3c-revert: This 3c's attempt at (2), so we can compare this diff to that one
# (4) orig --> 3c-orig: This is 3c's attempt at converting the original. We can compare this diff against (3) to see how much of what was achieved here approximates what's achieved there


# TODO: Different diff command? See below

set -o errexit
set -o nounset

echo "TEST,REFACTOR_LINES,REFACTOR_TOTAL,ANNOTATED_LINES,ANNOTATED_TOTAL" > diffs.sum

# pass the two folders to compare
function compute_diff() { 
  local added=$(diff -w $1 $2 | diffstat -s | awk '{ print $4 }')
  local delled=$(diff -w $1 $2 | diffstat -s | awk '{ print $6 }')
  echo $(( $added > $delled ? $added : $delled ))
}

# pass the folder to count
function count_lines() { 
  echo $(sloccount $1 | grep -e "^ansic" | awk '{ print $2 }')
}

for version in "manual" "revert" "orig" ; do 
  if [ "$version" = "manual" ]; then 
    ref=$(compute_diff "orig"  "revert" )
    ref_total=$(count_lines "orig" )
    anno=$(compute_diff "revert" "manual") 
    anno_total=$(count_lines "revert")
    echo "$version,$ref,$ref_total,$anno,$anno_total" >> diffs.sum
  elif [ "$version" = "revert" ]; then
    anno=$(compute_diff "revert" "3c-revert")
    anno_total=$(count_lines "revert") 
    echo "$version,N/A,N/A,$anno,$anno_total" >> diffs.sum
  elif [ "$version" = "orig" ]; then 
    anno=$(compute_diff "orig" "3c-revert") 
    anno_total=$(count_lines "orig") 
    echo "$version,N/A,N/A,$anno,$anno_total" >> diffs.sum
  fi
done



