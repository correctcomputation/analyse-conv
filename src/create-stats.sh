#!/bin/bash
# Computes statistics about the diffs between various versions of a target

# Rationale for these diff pairs:
# (1) orig --> revert: This is the refactoring work
# (2) revert --> manual: This is the annotation work
# (3) revert --> 3c-revert: This 3c's attempt at (2), so we can compare this diff to that one
# (4) orig --> 3c-orig: This is 3c's attempt at converting the original. We can compare this diff against (3) to see how much of what was achieved here approximates what's achieved there


# TODO: Different diff command -- should ignore differences due to the `_Unchecked` annotation

set -o errexit
set -o nounset

echo "TEST,REFACTOR_LINES,REFACTOR_TOTAL,ANNOTATED_LINES,ANNOTATED_TOTAL,LEFT_LINES,LEFT_TOTAL" > diffs.sum

# pass the two folders to compare
function compute_diff() { 
  local added=$(diff -w $1 $2 | diffstat -s | awk '{ print $4 }')
  if [ -z $added ]; then 
    added=0
  fi
  local delled=$(diff -w $1 $2 | diffstat -s | awk '{ print $6 }')
  if [ -z $delled ]; then 
    delled=0 
  fi
  echo $(( $added > $delled ? $added : $delled ))
}

# pass the two folders to compare
function compute_filtered_diff() { 
  local workfile=$(mktemp)
  for file in $(ls $1); do 
    cat "$2/$file" | ../../filter.sh | diff -w "$1/$file" - >> $workfile
  done
  local added=$(cat $workfile | diffstat -s | awk '{ print $4 }')
  if [ -z $added ]; then 
    added=0
  fi
  local delled=$(cat $workfile | diffstat -s | awk '{ print $6 }')
  if [ -z $delled ]; then 
    delled=0 
  fi
  echo $(( $added > $delled ? $added : $delled ))
}

# pass the folder to count
function count_lines() { 
  echo $(sloccount $1 | grep -e "^ansic" | awk '{ print $2 }')
}

for version in "manual" "revert" "tweak" "orig" ; do 
  if [ "$version" = "manual" ]; then 
    ref=$(compute_diff "orig-em"  "revert" )
    ref_total=$(count_lines "orig-em" )
    anno=$(compute_filtered_diff "revert" "manual-em") 
    anno_total=$(count_lines "revert")
    echo "$version,$ref,$ref_total,$anno,$anno_total,N/A,N/A" >> diffs.sum
  elif [ "$version" = "revert" ]; then
    anno=$(compute_diff "revert" "3c-revert")
    anno_total=$(count_lines "revert") 
    left=$(compute_filtered_diff "3c-revert" "manual-em")
    left_total=$(count_lines "3c-revert") 
    echo "$version,N/A,N/A,$anno,$anno_total,$left,$left_total" >> diffs.sum
  elif [ "$version" = "tweak" ]; then
    if [ -d "tweak" ]; then
      ref=$(compute_diff "orig-em"  "tweak-em" )
      ref_total=$(count_lines "orig-em" )
      anno=$(compute_diff "tweak-em" "3c-tweak") 
      anno_total=$(count_lines "tweak-em") 
      left=$(compute_filtered_diff "3c-tweak" "manual-em")
      left_total=$(count_lines "3c-tweak") 
      echo "$version,$ref,$ref_total,$anno,$anno_total,$left,$left_total" >> diffs.sum
    fi
  elif [ "$version" = "orig" ]; then 
    anno=$(compute_diff "orig-em" "3c-orig") 
    anno_total=$(count_lines "orig-em") 
    left=$(compute_filtered_diff "3c-orig" "manual-em")
    left_total=$(count_lines "3c-orig") 
    echo "$version,N/A,N/A,$anno,$anno_total,$left,$left_total" >> diffs.sum
  fi
done



