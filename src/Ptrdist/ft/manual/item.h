/*
 * item.h
 *
 * The author of this software is Alain K\"{a}gi.
 *
 * Copyright (c) 1993 by Alain K\"{a}gi and the University of Wisconsin
 * Board of Trustees.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose without fee is hereby granted, provided that this entire notice
 * is included in all copies of any software which is or includes a copy
 * or modification of this software and in all copies of the supporting
 * documentation for such software.
 *
 * THIS SOFTWARE IS BEING PROVIDED "AS IS", WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY.  IN PARTICULAR, NEITHER THE AUTHOR NOR THE UNIVERSITY OF
 * WISCONSIN MAKE ANY REPRESENTATION OR WARRANTY OF ANY KIND CONCERNING
 * THE MERCHANTABILITY OF THIS SOFTWARE OR ITS FITNESS FOR ANY PARTICULAR
 * PURPOSE.
 *
 * ------------------------------------------------------------------------
 *
 * Interface between graph and Fheap.
 *
 * ------------------------------------------------------------------------
 *
 * $Id$
 *
 */

#ifndef _item_h
#define _item_h

#include "graph.h"

#pragma CHECKED_SCOPE ON

typedef Vertices Item;

#define NULL_ITEM	NULL_VERTEX

int LessThan(_Ptr<Item> , _Ptr<Item> );
int Equal(_Ptr<Item> , _Ptr<Item> );
_Ptr<Item>  Subtract(_Ptr<Item> , int);

#pragma CHECKED_SCOPE OFF

#endif
