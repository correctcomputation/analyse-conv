PROG       = treeadd
SOURCES = args.c node.c par-alloc.c
HDRS = tree.h

CFLAGS   = -DTORONTO
LDFLAGS    = 
C3FLAGS = -c

ifdef SMALL_PROBLEM_SIZE
RUN_OPTIONS = 20
else ifdef LARGE_PROBLEM_SIZE
RUN_OPTIONS = 29
else
RUN_OPTIONS = 22
ifeq ($(ARCH),XCore)
XCORE_TARGET_NEEDS_MEMORY := 128
endif
endif
OUTPUT = treeadd.reference_output

PATH_TO_SRC = ../../

include $(PATH_TO_SRC)Makefile.common

