#!/bin/bash
# Computes statistics about the diffs between various versions of a target

# Rationale for these diff pairs:
# (1) orig --> revert: This is the refactoring work
# (2) revert --> manual: This is the annotation work
# (3) revert --> 3c-revert: This 3c's attempt at (2), so we can compare this diff to that one
# (4) orig --> 3c-orig: This is 3c's attempt at converting the original. We can compare this diff against (3) to see how much of what was achieved here approximates what's achieved there


# TODO: Different diff command? See below

echo "TEST,TOTAL_LINES,LINES_CHANGED,INSERTED,DELETED,MODIFIED,UNCHANGED" > diffs.dat
echo "TEST,TOTAL_LINES,LINES_CHANGED" > diffs.sum
for pair in "orig>revert" "revert>manual" "revert>3c-revert" "orig>3c-orig" ; do
	first=$(echo $pair | cut -d ">" -f 1)
	second=$(echo $pair | cut -d ">" -f 2)
	if [ -d $first ] && [ -d $second ] ; then
		echo "# $first-to-$second" >> diffs.dat
		#echo "# $first-to-$second" >> diffs.sum
		# TODO: Reconsider diff line, here
		# git diff -w --no-index --numstat $first $second ?
    test_name="$first-to-$second"
    if [ "$test_name" = "orig-to-revert" ]; then
      added=$(diff -w orig revert | diffstat -s | awk '{ print $4 }')
      delled=$(diff -w orig revert | diffstat -s | awk '{ print $6 }')
      total_lines=$(sloccount orig | grep -e "^ansic" | awk '{ print $2 }')
      refactored=$(( $added > $delled ? $added : $delled ))
      echo "$test_name,$total_lines,$refactored" >> diffs.sum
    else 
      echo "$test_name,N/A,N/A" >> diffs.sum
    fi 
	fi
done

