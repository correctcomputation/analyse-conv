





































#ifndef _fheap_h
#define _fheap_h











#include "item.h"

typedef struct _Heap
{
  Item * item;

  struct _Heap * parent;
  struct _Heap * child;
  struct _Heap * forward;
  struct _Heap * backward;
  int rank;
  short marked;
} HeapP;

#define NULL_HEAP	((void *)0)














void InitFHeap();













HeapP * MakeHeap();














Item * FindMin(HeapP * h);















HeapP * Insert(HeapP * * h, Item * i);













HeapP * Meld(HeapP * h1, HeapP * h2);













HeapP * DeleteMin(HeapP * h);

















HeapP * DecreaseKey(HeapP * h, HeapP * i, int delta);















HeapP * Delete(HeapP * h, HeapP * i);
















HeapP * Find(HeapP * h, Item * item);













Item * ItemOf(HeapP * h);

#endif
