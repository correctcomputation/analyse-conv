SOURCES = args.c newbh.c util.c walksub.c
HDRS = code.h defs.h stdinc.h vectmath.h
PROG     = bh
VERSIONS = orig manual 3c-manual 3c-em-orig revert-em-manual 3c-revert-em-manual tweak 3c-em-tweak

CFLAGS = -fcommon -DTORONTO
LDFLAGS  = -lm

ifdef LARGE_PROBLEM_SIZE
RUN_OPTIONS = 40000 30
else
ifdef SMALL_PROBLEM_SIZE
RUN_OPTIONS = 2000 5
else
RUN_OPTIONS = 20000 20
endif
endif
OUTPUT = bh.reference_output

PATH_TO_SRC = ../../

include $(PATH_TO_SRC)Makefile.common

