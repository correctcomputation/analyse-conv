#!/bin/bash

# requires NAME

PUSH= #set to anything to push changes, set to nothing to skip push
BRANCH=$(git rev-parse --abbrev-ref HEAD)

if ! git diff-index --quiet HEAD --; then
    echo please commit your changes, this script needs to change branches
	exit 1
fi

if make git-orig ; then
	git checkout -B $NAME-diff-orig
	make add-git
	git commit -m"$NAME: setup originals"
	[ ! -z $PUSH ] && git push --set-upstream origin $NAME-diff-orig

	if make git-3c-orig ; then
		git checkout -B $NAME-diff-3c-orig
		make add-git
		git commit -m"$NAME: convert to 3c version"
		[ ! -z $PUSH ] && git push --set-upstream origin $NAME-diff-3c-orig

		if make git-manual ; then
			git checkout -B $NAME-diff-manual
			make add-git
			git commit -m"$NAME: replace with manual version"
			[ ! -z $PUSH ] && git push --set-upstream origin $NAME-diff-manual

			if make git-revert ; then
				git checkout -B $NAME-diff-revert
				make add-git
				git commit -m"$NAME: remove checkedc annotations"
				[ ! -z $PUSH ] && git push --set-upstream origin $NAME-diff-revert

				if make git-3c-revert ; then
					git checkout -B $NAME-diff-3c-revert
					make add-git
					git commit -m"$NAME: reconvert to 3c version"
					[ ! -z $PUSH ] && git push --set-upstream origin $NAME-diff-3c-revert
				fi
			fi
		fi
	fi
fi

git checkout $BRANCH
echo "New git branches were added with git-diffs/ filled with relavant files"

