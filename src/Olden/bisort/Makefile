SOURCES = args.c bitonic.c
HDRS = node.h proc.h
PROG     = bisort

CFLAGS = -DTORONTO
LDFLAGS  = -lm

ifdef LARGE_PROBLEM_SIZE
RUN_OPTIONS = 40000000
HASH_PROGRAM_OUTPUT = 1
else
RUN_OPTIONS = 700000
OUTPUT = bisort.reference_output
endif

STDIN_FILENAME = /dev/stdin

PATH_TO_SRC = ../../

# special handling of stdchecked macros
C3 := $(C3) -c

include $(PATH_TO_SRC)Makefile.common

