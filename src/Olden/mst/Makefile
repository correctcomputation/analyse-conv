PROG       = mst
SOURCES = args.c makegraph.c hash.c main.c
HDRS = hash.h mst.h
VERSIONS = orig manual 3c-manual 3c-em-orig revert-em-manual 3c-revert-em-manual tweak 3c-em-tweak

CFLAGS   = -DTORONTO
LDFLAGS    =
C3FLAGS = -c

ifdef LARGE_PROBLEM_SIZE
RUN_OPTIONS = 10000
else
RUN_OPTIONS = 1000
endif
OUTPUT = mst.reference_output

PATH_TO_SRC = ../../

include $(PATH_TO_SRC)Makefile.common

