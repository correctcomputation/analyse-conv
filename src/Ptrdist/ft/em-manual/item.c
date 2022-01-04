





























#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "item.h"

#pragma CHECKED_SCOPE ON

int LessThan(_Ptr<Item> item1, _Ptr<Item> item2)
{
  return(((*(item1)).key) < ((*(item2)).key));
}

int Equal(_Ptr<Item> item1, _Ptr<Item> item2)
{
  return(((*(item1)).key) == ((*(item2)).key));
}

_Ptr<Item> Subtract(_Ptr<Item> item, int delta)
{
    ((void) sizeof ((delta > 0) ? 1 : 0), __extension__ ({ if (delta > 0) ; else __assert_fail ("delta > 0", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/item.c", 51, __extension__ __PRETTY_FUNCTION__); }));

    ((*(item)).key) = ((*(item)).key) - delta;

    return(item);
}

