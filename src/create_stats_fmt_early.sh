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
  local added=$(git diff --shortstat --word-diff --no-index $1 $2 | awk '{ print $4 }')
  if [ -z $added ]; then 
    added=0
  fi
  local delled=$(git diff --shortstat --word-diff --no-index $1 $2| awk '{ print $6 }')
  if [ -z $delled ]; then 
    delled=0 
  fi
  echo $(( $added > $delled ? $added : $delled ))
}

# pass the two folders to compare
function compute_filtered_diff() {
  make filter-$2 &>/dev/null
  local added=$(git diff --shortstat --word-diff --no-index $1 filter-$2 | awk '{ print $4 }')
  if [ -z $added ]; then 
    added=0
  fi
  local delled=$(git diff --shortstat --word-diff --no-index $1 filter-$2 | awk '{ print $6 }')
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
    ref=$(compute_diff "fmt-em-orig_early"  "fmt-revert-em-manual_early" )
    ref_total=$(count_lines "fmt-em-orig_early" )
    anno=$(compute_filtered_diff "fmt-revert-em-manual_early" "fmt-em-manual_early")
    anno_total=$(count_lines "fmt-revert-em-manual_early")
    echo "$version,$ref,$ref_total,$anno,$anno_total,N/A,N/A" >> diffs.sum
  elif [ "$version" = "revert" ]; then
    anno=$(compute_diff "fmt-revert-em-manual_early" "fmt-3c-revert-em-manual_early")
    anno_total=$(count_lines "fmt-revert-em-manual_early")
    left=$(compute_filtered_diff "fmt-3c-revert-em-manual_early" "fmt-em-manual_early")
    left_total=$(count_lines "fmt-3c-revert-em-manual_early")
    echo "$version,N/A,N/A,$anno,$anno_total,$left,$left_total" >> diffs.sum
  elif [ "$version" = "tweak" ]; then
    if [ -d "tweak" ]; then
      ref=$(compute_diff "fmt-em-orig_early"  "fmt-em-tweak" )
      ref_total=$(count_lines "fmt-em-orig_early" )
      anno=$(compute_diff "fmt-em-tweak" "fmt-3c-em-tweak")
      anno_total=$(count_lines "fmt-em-tweak")
      left=$(compute_filtered_diff "fmt-3c-em-tweak" "fmt-em-manual_early")
      left_total=$(count_lines "fmt-3c-em-tweak")
      echo "$version,$ref,$ref_total,$anno,$anno_total,$left,$left_total" >> diffs.sum
    fi
  elif [ "$version" = "orig" ]; then 
    anno=$(compute_diff "fmt-em-orig_early" "fmt-3c-em-orig_early")
    anno_total=$(count_lines "fmt-em-orig_early")
    left=$(compute_filtered_diff "fmt-3c-em-orig_early" "fmt-em-manual_early")
    left_total=$(count_lines "fmt-3c-em-orig_early")
    echo "$version,N/A,N/A,$anno,$anno_total,$left,$left_total" >> diffs.sum
  fi
done



