#!/bin/bash

if [ $# != 2 ]; then
    echo "usage $0 base-C-dir base-3C-output-dir"
    exit 1
fi

orig=$1
threecout=$2

# find all files only present in the one dir
files=$(diff -qr $orig $threecout | awk '/^Only in/ { printf "%s/%s\n",substr($3,0,length($3)-1),$4 }')

for file in $files; do
    # copy those from the base dir to output dir
    if [ "${file#$orig/}" != "${file}" ]; then
	echo "cp $file $threecout/${file#$orig/}"
	cp $file $threecout/${file#$orig/}
    else
	echo "WARNING: file $file only in $threecout"
    fi
done
