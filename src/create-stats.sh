#!/bin/bash

declare -A summation

echo "INSERTED,DELETED,MODIFIED,UNCHANGED,FILENAME" > diffs.dat
echo "INSERTED,DELETED,MODIFIED,UNCHANGED,FILENAME" > diffs.sum
for pair in "3c-orig>manual" "orig>3c-orig" "manual>revert" "revert>3c-revert" ; do
	first=$(echo $pair | cut -d ">" -f 1)
	second=$(echo $pair | cut -d ">" -f 2)
	if [ -d $first ] && [ -d $second ] ; then
		echo "# $first-to-$second" >> diffs.dat
		echo "# $first-to-$second" >> diffs.sum
		lines=$(diff $first $second | diffstat -t -S$first | sed '1d')
		summation[ins]=0
		summation[del]=0
		summation[mod]=0
		summation[unc]=0
		while IFS=, read -r ins del mod unc fil; do
			summation[ins]=$((summation[ins]+$ins))
			summation[del]=$((summation[del]+$del))
			summation[mod]=$((summation[mod]+$mod))
			summation[unc]=$((summation[unc]+$unc))
		done < <(echo -e "$lines")
		echo -e "$lines" >> diffs.dat
		echo -e "${summation[ins]},${summation[del]},${summation[mod]},${summation[unc]},$NAME" \
			 >> diffs.sum
		echo -e "\n" >> diffs.dat # this is 2 spaces, as required
		echo -e "\n" >> diffs.sum # this is 2 spaces, as required
	fi
done

