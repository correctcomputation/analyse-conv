# analyse-conv
For analysing addition and removal of checkedc extensions, for use with 3C and C3

# requirements
```
export CC=path/to/checkedc/compiler
export THREEC=path/to/converter
export C3=path/to/deconverter
```

# Usage
each sample project has 2 versions of its source code:
- orig: c version
- manual: checkedc version, manually ported from the c version
to create more:
```
cd src/<project>
make
```
this will attempt to create 3 additional versions
- orig-3c: "orig" automatically converted to checkedc
- revert: "manual" automatically deconverted c
- 3c-revert: "revert" automatically reconverted to checkedc

for convenience you can also
```
make git-diffs
```
to create git branches that have a single directory changed one step at a time

you can set to automatically push these changes to the repo by changing `PUSH` in `src/create-git-diffs.sh`. You may want to manually make pull requests to use the full github interface.

# more make targets
- make <version>: do things one at a time
- make test-<version>: run the compiler on the results, and execute the provided test 
- make test: run the compiler on all results (failure will stop the process)
- make clean: delete all but the starter files (no change to git branches)
- make clean-<version>: just delete one

# getting more samples
Each sample project requires c code and checkedc code in `orig` and `manual` directories respectively. They also need a `Makefile` with a list of the file names, and a test. This should include the common makefile to allow all the targets. See one of the other projects' `Makefile` for an example.

