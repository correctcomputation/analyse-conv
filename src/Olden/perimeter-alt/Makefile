PROG     = perimeter
SOURCES = args.c main.c maketree.c
HDRS = perimeter.h

CFLAGS = -DTORONTO
LDFLAGS  = 

ifdef LARGE_PROBLEM_SIZE
RUN_OPTIONS = 12
else ifdef SMALL_PROBLEM_SIZE
RUN_OPTIONS = 9
else
RUN_OPTIONS = 10
ifeq ($(ARCH),XCore)
XCORE_TARGET_NEEDS_MEMORY := 64
endif
endif
OUTPUT = perimeter.reference_output
STDIN_FILENAME = /dev/stdin

PATH_TO_SRC = ../../

# special handling of stdchecked macros
C3 := $(C3) -c

include $(PATH_TO_SRC)Makefile.common

