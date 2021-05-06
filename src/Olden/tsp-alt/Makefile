PROG     = tsp
SOURCES = args.c build.c main.c tsp.c
HDRS = tsp.h

CFLAGS = -DTORONTO
LDFLAGS  = -lm

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
STDIN_FILENAME = /dev/stdin

PATH_TO_SRC = ../../

# special handling of stdchecked macros
C3 := $(C3) -c

include $(PATH_TO_SRC)Makefile.common
