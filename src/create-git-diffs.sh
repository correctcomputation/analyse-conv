#!/bin/bash

# requires NAME

PUSH=
BRANCH=$(git rev-parse --abbrev-ref HEAD)

if ! git diff-index --quiet HEAD --; then
    echo please commit your changes, this script needs to change branches
	exit 1
fi

git checkout -B $NAME-diff-orig
mkdir -p git-changes
if cp orig/* git-changes/ ; then
	git add git-changes/*
	git commit -m"$NAME: setup originals"
	[ -v $PUSH ] && git push --set-upstream origin $NAME-diff-orig

	git checkout -B $NAME-diff-3c-orig
	if cp 3c-orig/* git-changes ; then
		git add git-changes/*
		git commit -m"$NAME: convert to 3c version"
		[ -v $PUSH ] && git push --set-upstream origin $NAME-diff-3c-orig

		git checkout -B $NAME-diff-manual
		if cp manual/* git-changes ; then
			git add git-changes/*
			git commit -m"$NAME: replace with manual version"
			[ -v $PUSH ] && git push --set-upstream origin $NAME-diff-manual

			git checkout -B $NAME-diff-revert
			if cp revert/* git-changes ; then
				git add git-changes/*
				git commit -m"$NAME: remove checkedc annotations"
				[ -v $PUSH ] && git push --set-upstream origin $NAME-diff-revert

				git checkout -B $NAME-diff-3c-revert
				if cp 3c-revert/* git-changes ; then
					git add git-changes/*
					git commit -m"$NAME: reconvert to 3c version"
					[ -v $PUSH ] && git push --set-upstream origin $NAME-diff-3c-revert
				fi
			fi
		fi
	fi
fi

git checkout $BRANCH


