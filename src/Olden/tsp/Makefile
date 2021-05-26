PROG     = tsp
SOURCES = args.c build.c main.c tsp.c
HDRS = tsp.h
VERSIONS ?= orig manual 3c-manual 3c-em-orig revert-em-manual 3c-revert-em-manual tweak 3c-em-tweak

CFLAGS = -DTORONTO
LDFLAGS  = -lm
C3FLAGS = -c

ifdef LARGE_PROBLEM_SIZE
RUN_OPTIONS = 40960000
else
ifdef SMALL_PROBLEM_SIZE
RUN_OPTIONS = 102400
else
RUN_OPTIONS = 1024000
ifeq ($(ARCH),XCore)
XCORE_TARGET_NEEDS_MEMORY := 64
endif
endif
endif
OUTPUT = tsp.reference_output

PATH_TO_SRC = ../../

include $(PATH_TO_SRC)Makefile.common
