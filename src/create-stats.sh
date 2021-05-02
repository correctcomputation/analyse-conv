#!/bin/bash
# Computes statistics about the diffs between various versions of a target

# Rationale for these diff pairs:
# (1) orig --> revert: This is the refactoring work
# (2) revert --> manual: This is the annotation work
# (3) revert --> 3c-revert: This 3c's attempt at (2), so we can compare this diff to that one
# (4) orig --> 3c-orig: This is 3c's attempt at converting the original. We can compare this diff against (3) to see how much of what was achieved here approximates what's achieved there

# breaks on MacOS; seems to not be needed
# declare -A summation

# TODO: Different diff command? See below

echo "INSERTED,DELETED,MODIFIED,UNCHANGED,FILENAME" > diffs.dat
echo "INSERTED,DELETED,MODIFIED,UNCHANGED,FILENAME" > diffs.sum
for pair in "orig>revert" "revert>manual" "revert>3c-revert" "orig>3c-orig" ; do
	first=$(echo $pair | cut -d ">" -f 1)
	second=$(echo $pair | cut -d ">" -f 2)
	if [ -d $first ] && [ -d $second ] ; then
		echo "# $first-to-$second" >> diffs.dat
		echo "# $first-to-$second" >> diffs.sum
		# TODO: Reconsider diff line, here
		# git diff -w --no-index --numstat $first $second ?
		lines=$(diff -w $first $second | diffstat -t -S$first | sed '1d')
		summation[ins]=0
		summation[del]=0
		summation[mod]=0
		summation[unc]=0
		if [[ ! -z $lines ]]; then
      ins=$(echo $lines | awk 'BEGIN { FS = "," } { print $1 }')
      del=$(echo $lines | awk 'BEGIN { FS = "," } { print $2 }')
      chg=$(echo $lines | awk 'BEGIN { FS = "," } { print $3 }')
      total=$(echo "$ins $del $chg + p" | dc)
			echo -e "$lines" >> diffs.dat
      echo -e "$total" >> diffs.sum
		fi
		echo -e "\n" >> diffs.dat # this is 2 spaces, as required
		echo -e "\n" >> diffs.sum # this is 2 spaces, as required
	fi
done

