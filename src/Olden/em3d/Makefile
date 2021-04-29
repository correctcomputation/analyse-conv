SOURCES = args.c em3d.c main.c make_graph.c util.c
HDRS = em3d.h make_graph.h util.h
PROG       = em3d

CFLAGS   = -DTORONTO -I..
LDFLAGS    = 

ifdef SMALL_PROBLEM_SIZE
RUN_OPTIONS = 256 250 35
else ifdef LARGE_PROBLEM_SIZE
RUN_OPTIONS = 3072 3000 750
else
RUN_OPTIONS = 1024 1000 125
OUTPUT = em3d.reference_output
endif
STDIN_FILENAME = /dev/stdin

PATH_TO_SRC = ../../

include $(PATH_TO_SRC)Makefile.common

