# analyse-conv
For analysing addition and removal of checkedc extensions, for use with 3C and C3

# requirements
```
export CC=path/to/checkedc/compiler
export THREEC=path/to/converter
export C3=path/to/deconverter
export THREEC_WORKTREE=path/to/3c-worktree
```
(`THREEC_WORKTREE` should be the 3C worktree root: that is, the directory
containing `clang/tools/3c`, etc. It is used to run the macro expander.)

# Running the expirement 
Run `make` to produce the tables 

`final.tex` is the table in latex 

`final.txt` is an ascii table

# Convert
each sample project has 2 versions of its source code:
- orig: c version
- manual: checkedc version, manually ported from the c version

To create more:
```
cd src/<project>
make
```
this will attempt to create 3 additional versions
- orig-3c: "orig" automatically converted to checkedc
- revert: "manual" automatically deconverted c
- 3c-revert: "revert" automatically reconverted to checkedc

You can also use `make` from any directory and it will make all sub-projects

To build all 5 versions of a project and save the build logs (errors, etc.) and
a compilation database that you can use to experiment with the code in an IDE,
run:

```
make bear-test
```

in `src` or any descendant directory.

# Analyse

After conversion is done you can make diffs or generate their stats
Any failed conversions will not be included in the stats (needs to be confirmed for more cases)

```
make git-diffs
```
to create git branches that have a single directory changed one step at a time. These branches are reused on repeated creation, so there is also a datestamped branch for the final one.

You may want to check the results by using `git log --oneline --graph --all` to see all the branches.

you can set to automatically push these changes to the repo by changing `PUSH` in `src/create-git-diffs.sh`. You may want to manually make pull requests to use the full github interface.

you can also show the diff stats:
```
make stats
```
this will create a file `diffs.dat` showing the number of changes per file per conversion, and `diffs.sum` showing the total number for the project

# more make targets
- `make <version>`: do things one at a time
- `make test-<version>`: run the compiler on the results, and execute the provided test 
- `make test`: run the compiler on all results (failure will stop the process)
- `make clean`: delete all but the starter files (no change to git branches)
- `make clean-<version>`: just delete one

all of these can be called from any directory to apply to all sub-projects

# getting more samples
Each sample project requires c code and checkedc code in `orig` and `manual` directories respectively. They also need a `Makefile` with a list of the file names, and a test. This should include the common makefile to allow all the targets. See one of the other projects' `Makefile` for an example. Directories with collections of projects need a makefile as well, see Ptrdist for a sample.

