# analyse-conv
For analysing addition and removal of checkedc extensions, for use with 3C and C3

# requirements
we need the paths to our tools to use them, you can add them to /tools/Makefile.config (see .template) or on the command line:
```
export FMT=path/to/checkedc/clang-format
export CCClang=path/to/checkedc/compiler
export THREEC=path/to/converter
export C3=path/to/deconverter
export THREEC_WORKTREE=path/to/3c-worktree
```
(`THREEC_WORKTREE` should be the 3C worktree root: that is,
`$THREEC_WORKTREE/clang/tools/3c` should exist. This is used to run the macro
expander.)

# Running the expirement 
Run `make` to produce the tables 

`final.tex` is the table in latex 

`final.txt` is an ascii table

# Convert
each sample project has at least 2 versions of its source code:
- orig: c version
- manual: checkedc version, manually ported from the c version
most also have
- orig_early: orig version unmodified from microsoft test suite
- manual_early: manual version unmodified from microsoft test suite

You may add more directories with source files as well.

To create more:
```
cd src/<project>
make
```
this will attempt to create additional versions based on the `VERSIONS` variable in that project's makefile.
The current default is to make:
- 3c-em-orig: "orig" automatically converted to checkedc after macro expansion
- revert-em-manual: "manual" automatically deconverted c after macro expansion
- 3c-revert-em-manual: the previous result automatically reconverted to checkedc
- 3c-manual: "manual" converted to 3c without macro expansion, used primarilly for the generated statistics

Our tools "fmt", "em", "3c", and "revert" can be used arbitrarily in make targets i.e. `make 3c-em-manual`. The only restriction is that make will not repeat a tool automatically, but will if the partial result exists. You can override `VERSIONS` to handle this. So to create `3c-revert-3c-orig` run `make VERSIONS='revert-3c-orig 3c-revert-3c-orig'`. You may also use custom base directories i.e. `make 3c-tweak` if `tweak/` exists.

"fmt" uses a `.clang-format` file in /src, but one can be added to a deeper directory to control local changes.

You can also use `make` from any directory and it will make all sub-projects

To build all versions of a project and save the build logs (errors, etc.) and
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

# more make targets
- `make <version>`: do things one at a time
- `make test-<version>`: run the compiler on the results, and execute the provided test 
- `make test`: run the compiler on all results (failure will stop the process)
- `make clean`: delete all but the starter files (no change to git branches)
- `make clean-<version>`: just delete one

all of these can be called from any directory to apply to all sub-projects

# getting more samples
Each sample project requires c code and checkedc code in a base directory (usually `orig` and `manual`). They also need a `Makefile` with lists of the file names, and a test. You may also want to include the VERSIONS for this project if they are different from the default. You need to include the common makefile to allow all the targets. See one of the other projects' `Makefile` for an example. Directories with collections of projects need a makefile as well, see Ptrdist for a sample.

