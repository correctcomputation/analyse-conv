#!/bin/bash

echo "INSERTED,DELETED,MODIFIED,UNCHANGED,FILENAME" > diffs.dat
for pair in "3c-orig>manual" "orig>3c-orig" "manual>revert" "revert>3c-revert" ; do
	first=$(echo $pair | cut -d ">" -f 1)
	second=$(echo $pair | cut -d ">" -f 2)
	if [ -d $first ] && [ -d $second ] ; then
		echo "# $first-to-$second" >> diffs.dat
		diff $first $second | diffstat -t -S$first | sed '1d' >> diffs.dat
		echo -e "\n" >> diffs.dat # this is 2 spaces, as required
	fi
done

