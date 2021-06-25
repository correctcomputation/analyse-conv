GCC = gcc -g -std=c99 -Wall -Wshadow -Wvla -pedantic -O3
VAL = valgrind -s --leak-check=full --leak-check=full --show-leak-kinds=all --track-origins=yes

SRCS = pa4.c eval.c build.c manip.c
OBJS = $(SRCS:%.c=%.o)

pa4: $(OBJS)
	$(GCC) $(OBJS) -o pa4
	
.c.o:
	$(GCC) -c $*.c

testmemory: pa4
		$(VAL) --log-file=memcheck.txt ./pa4 -b examples/ops3.b treeOutput3


testall: test1 test2 test3 test4 test5 test6 test7 test9 test10 test11 test12

test1: pa4
	./pa4 -e examples/invalidtree0.b
test2: pa4
	./pa4 -e examples/invalidtree1.b
test3: pa4
	./pa4 -e examples/invalidtree2.b
test4: pa4
	./pa4 -e examples/invalidtree4.b
test5: pa4
	./pa4 -b examples/ops0.b treeOutput0
	diff treeOutput0 examples/tree0.b
test6: pa4
	./pa4 -b examples/ops1.b treeOutput1
	diff treeOutput1 examples/tree1.b
test7: pa4
	./pa4 -b examples/ops2.b treeOutput2 2>errLog
	diff treeOutput2 examples/tree2.b
test8: pa4
	./pa4 -b examples/ops3.b treeOutput3 2>errLog
	diff treeOutput3 examples/tree3.b
test9: pa4
	./pa4 -e examples/tree0.b
test10: pa4
	./pa4 -e examples/tree1.b
test11: pa4
	./pa4 -e examples/tree2.b
test12: pa4
	./pa4 -e examples/tree3.b

clean: # remove all machine generated files
	rm -f *.o memcheck?.txt pa4 treeOutput?
	
zip:
	zip pa4.zip *.c *.h Makefile 
