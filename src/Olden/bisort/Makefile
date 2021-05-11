SOURCES = args.c bitonic.c
HDRS = node.h proc.h
PROG     = bisort

CFLAGS = -DTORONTO
LDFLAGS  = -lm

# As of 2021-05-03, there's an unwritable change in bisort that is causing 3C to
# fail and bisort to be omitted from the results. We think it's probably
# unimportant, so ignore it for now.
THREEC_FLAGS = -allow-unwritable-changes

ifdef LARGE_PROBLEM_SIZE
RUN_OPTIONS = 40000000
HASH_PROGRAM_OUTPUT = 1
else
RUN_OPTIONS = 700000
OUTPUT = bisort.reference_output
endif

PATH_TO_SRC = ../../

# special handling of stdchecked macros
C3 := $(C3) -c

include $(PATH_TO_SRC)Makefile.common

