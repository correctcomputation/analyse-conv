#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct _Node {
   long value;
   struct _Node *next;
} Node;

typedef struct _List {
	Node* head;
	Node* tail;
} List;

Node *List_Load_From_File(char *filename);

int List_Save_To_File(char *filename, Node *list);

Node *List_Shellsort(Node *list, long *n_comp);

List* addNode(List* list, long val);

Node* destroyList(Node* head);

Node* swapNodes(Node* head, int pos1, int pos2);

Node* getNodeAtIndex(Node* head, long index);

void printList(Node* head);
