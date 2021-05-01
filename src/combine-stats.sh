#!/bin/bash

# requires
# NAME
# TARGETS

declare -A diffs
declare -A summation

VERSIONS="orig-to-3c-orig 3c-orig-to-manual manual-to-revert revert-to-3c-revert"
for v in $VERSIONS; do
	diffs[$v]=""
done

echo "INSERTED,DELETED,MODIFIED,UNCHANGED,FILENAME" > diffs.dat
echo "INSERTED,DELETED,MODIFIED,UNCHANGED,FILENAME" > diffs.sum
for target in $TARGETS; do
	while read -r line; do
		if [[ -z $line ]] || [[ $line = INSERTED* ]]; then continue; fi
		if [[ $line =~ ^#.* ]]; then
			lastversion=$(echo $line | sed 's/^..//')
		else
			diffs[$lastversion]="${diffs[$lastversion]}$line\n"
		fi
	done < "$target/diffs.sum"
done

for v in $VERSIONS ; do
	echo "# $v" >> diffs.dat
	echo "# $v" >> diffs.sum
	lines=${diffs[$v]%??} # removes trainling \n so read won't fill in blanks later
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
done

