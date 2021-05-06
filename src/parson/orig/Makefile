CC = clang
CFLAGS = -O0 -g -Wall -Wextra -std=c99 -pedantic-errors

all: test
OBJ = tests.o parson.o 

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f test *.o
