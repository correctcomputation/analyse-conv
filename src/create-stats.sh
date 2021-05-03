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
		lines=$(diff -w $first $second | diffstat -t -S$first | sed '1d')
    test_lines=0
    test_changed=0
		if [[ ! -z $lines ]]; then
      echo $lines >> diffs.dat
      for line in $lines; do 
        ins=$(echo $lines | awk 'BEGIN { FS = "," } { print $1 }')
        del=$(echo $lines | awk 'BEGIN { FS = "," } { print $2 }')
        mod=$(echo $lines | awk 'BEGIN { FS = "," } { print $3 }')
        uch=$(echo $lines | awk 'BEGIN { FS = "," } { print $4 }')
        total_changed=$(echo "$ins $del $mod 0d[+2z>a]salaxp" | dc)
        total_lines=$(echo "$ins $del $mod $uch 0d[+2z>a]salaxp" | dc)
        test_lines=$(echo "$test_lines $total_lines + p" | dc)
        test_changed=$(echo "$test_changed $total_changed + p" | dc)
      done
      echo "$first-to-$second,$test_lines,$test_changed" >> diffs.sum
		fi
	fi
done

