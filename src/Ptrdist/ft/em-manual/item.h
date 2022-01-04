





























#ifndef _item_h
#define _item_h

#include "graph.h"

#pragma CHECKED_SCOPE ON

typedef Vertices Item;

#define NULL_ITEM	NULL_VERTEX

int LessThan(_Ptr<Item> item1, _Ptr<Item> item2);
int Equal(_Ptr<Item> item1, _Ptr<Item> item2);
_Ptr<Item> Subtract(_Ptr<Item> item, int delta);

#pragma CHECKED_SCOPE OFF

#endif
