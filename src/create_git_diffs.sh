#!/bin/bash

# requires NAME VERSIONS

PUSH= #set to anything to push changes, set to nothing to skip push
BRANCH=$(git rev-parse --abbrev-ref HEAD)

if ! git diff-index --quiet HEAD --; then
	echo "*******"
    echo "* Please commit your changes, this script needs to change branches"
	echo "*******"
	exit 1
fi

for ver in $VERSIONS ; do
	if make git-$ver ; then
		git checkout -B "${NAME}_diff-${ver}"
		make add_git_changes
		git commit -m"${NAME}_diff-${ver}"
		[ ! -z $PUSH ] && git push --set-upstream origin "${NAME}_diff-${ver}"
	fi
done

NOW=$(date '+%Y%m%d%H%M%S')
git checkout -b $NAME-$NOW
[ ! -z $PUSH ] && git push --set-upstream origin $NAME-$NOW

git checkout $BRANCH
echo "New git branches were added with git-diffs/ filled with relavant files"

