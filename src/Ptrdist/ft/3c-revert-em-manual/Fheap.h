





































#ifndef _fheap_h
#define _fheap_h











#include "item.h"


#define printf(...)  { (printf)(__VA_ARGS__); }
#define fprintf(...)  { (fprintf)(__VA_ARGS__); }

typedef struct _Heap
{
  _Ptr<Item> item;

  _Ptr<struct _Heap> parent;
  _Ptr<struct _Heap> child;
  _Ptr<struct _Heap> forward;
  _Ptr<struct _Heap> backward;
  int rank;
  short marked;
} HeapP;

#define NULL_HEAP	((void *)0)














void InitFHeap(void);













_Ptr<HeapP>  MakeHeap(void);














_Ptr<Item> FindMin(_Ptr<HeapP> h);















_Ptr<HeapP> Insert(_Ptr<_Ptr<HeapP>> h, _Ptr<Item> i);













_Ptr<HeapP> Meld(_Ptr<HeapP> h1, _Ptr<HeapP> h2);













_Ptr<HeapP> DeleteMin(_Ptr<HeapP> h);

















_Ptr<HeapP> DecreaseKey(_Ptr<HeapP> h, _Ptr<HeapP> i, int delta);















_Ptr<HeapP> Delete(_Ptr<HeapP> h, _Ptr<HeapP> i);
















_Ptr<HeapP> Find(_Ptr<HeapP> h, _Ptr<Item> item);













_Ptr<Item> ItemOf(_Ptr<HeapP> h);


#endif
