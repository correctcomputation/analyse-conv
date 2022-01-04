





























#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "item.h"

int LessThan(Item * item1, Item * item2)
{
  return(((*(item1)).key) < ((*(item2)).key));
}

int Equal(Item * item1, Item * item2)
{
  return(((*(item1)).key) == ((*(item2)).key));
}

Item * Subtract(Item * item, int delta)
{
    ((void) sizeof ((delta > 0) ? 1 : 0), __extension__ ({ if (delta > 0) ; else __assert_fail ("delta > 0", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-orig/item.c", 49, __extension__ __PRETTY_FUNCTION__); }));

    ((*(item)).key) = ((*(item)).key) - delta;

    return(item);
}

