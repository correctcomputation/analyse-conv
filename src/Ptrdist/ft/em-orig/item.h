





























#ifndef _item_h
#define _item_h

#include "graph.h"

typedef Vertices Item;

#define NULL_ITEM	NULL_VERTEX

int LessThan(Item *item1, Item *item2);
int Equal(Item *item1, Item *item2);
Item * Subtract(Item *item, int delta);

#endif
