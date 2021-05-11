PROG     = perimeter
SOURCES = args.c main.c maketree.c
HDRS = perimeter.h
VERSIONS = orig manual 3c-manual 3c-em-orig revert-em-manual 3c-revert-em-manual tweak 3c-em-tweak

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

PATH_TO_SRC = ../../

# special handling of stdchecked macros
C3 := $(C3) -c

include $(PATH_TO_SRC)Makefile.common

