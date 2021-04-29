PROG       = mst
SOURCES = args.c makegraph.c hash.c main.c
HDRS = hash.h mst.h

CFLAGS   = -DTORONTO
LDFLAGS    =

ifdef LARGE_PROBLEM_SIZE
RUN_OPTIONS = 10000
else
RUN_OPTIONS = 1000
endif
OUTPUT = mst.reference_output
STDIN_FILENAME = /dev/stdin

PATH_TO_SRC = ../../

include $(PATH_TO_SRC)Makefile.common

