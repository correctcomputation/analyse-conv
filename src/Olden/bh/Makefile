SOURCES = args.c newbh.c util.c walksub.c
HDRS = code.h defs.h stdinc.h vectmath.h
PROG     = bh

CFLAGS = -I.. -fcommon -DTORONTO
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
STDIN_FILENAME = /dev/stdin

PATH_TO_SRC = ../../

include $(PATH_TO_SRC)Makefile.common

