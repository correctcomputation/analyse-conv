#include <stdio_checked.h>
#include <string_checked.h>
#include <stdlib_checked.h>
#include <time_checked.h>

typedef struct _Node {
	long value;
	_Ptr<struct _Node> next;
} Node;

typedef struct _List {
	_Ptr<Node> head;
	_Ptr<Node> tail;
} List;

_Ptr<Node> List_Load_From_File(_Nt_array_ptr<char> filename);

size_t List_Save_To_File(_Nt_array_ptr<char> filename, _Ptr<Node> list);

_Ptr<Node> List_Shellsort(_Ptr<Node> list, _Ptr<long> n_comp);

_Ptr<List> addNode(_Ptr<List> list, long val);

_Ptr<Node> destroyList(_Ptr<Node> head);

_Ptr<Node> swapNodes(_Ptr<Node> head, int pos1, int pos2);

_Ptr<Node> getNodeAtIndex(_Ptr<Node> head, long index);

void printList(_Ptr<Node> head);
