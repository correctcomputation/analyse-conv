





































#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Fheap.h"
#include "Fstruct.h"


#ifdef DO_INLINE
#define INLINE inline
#else
#define INLINE
#endif

static _Ptr<HeapP> hTable _Checked[10000] = {((void *)0)};

void CombineLists(_Ptr<HeapP> h1, _Ptr<HeapP> h2);
void AddEntry(_Ptr<HeapP> h1, _Ptr<HeapP> h2);
_Ptr<HeapP> RemoveEntry(_Ptr<HeapP> h);
_Ptr<HeapP> NewHeap(_Ptr<Item> i);
void RemoveChild(_Ptr<HeapP> i);
void FixRank(_Ptr<HeapP> h, int delta);

       void
InitFHeap(void)
{
  int j;

  for(j = 0; j < 10000; j++)
  {
    hTable[j] = ((void*)0);
  }
}

       _Ptr<HeapP> 
MakeHeap(void)
{
  return(((void*)0));
}

       _Ptr<Item> FindMin(_Ptr<HeapP> h)
{
  if(h == ((void*)0))
  {
    return(((void*)0));
  }
  else
  {
    return(((*(h)).item));
  }
}

       _Ptr<HeapP> Insert(_Ptr<_Ptr<HeapP>> h, _Ptr<Item> i)
{
  _Ptr<HeapP> h1 = 0;

  h1 = NewHeap(i);
  *h = Meld(*h, h1);
  return(h1);
}

       _Ptr<HeapP> Meld(_Ptr<HeapP> h1, _Ptr<HeapP> h2)
{
  if(h2 == ((void*)0))
  {
    return(h1);
  }
  if(h1 == ((void*)0))
  {
    return(h2);
  }
  CombineLists(h1, h2);
  if(LessThan(((*(h1)).item), ((*(h2)).item)))
  {
    return(h1);
  }
  else
  {
    return(h2);
  }
}




       _Ptr<HeapP> DeleteMin(_Ptr<HeapP> h)
{
  int r, rMax, j;
  _Ptr<HeapP> h1 = 0;
  _Ptr<HeapP> h2 = 0;
  _Ptr<HeapP> h3 = 0;
  _Ptr<HeapP> min = 0;

  rMax = 0;

  if(h == ((void*)0))
  {
    return(((void*)0));
  }

  h1 = RemoveEntry(h);

  if(h1 == ((void*)0))
  {
    free<HeapP>(h);
    return(((void*)0));
  }




  if(h1 == ((*(h)).child))
  {
    ((*(h)).child) = ((void*)0);
  }




  h2 = h1;
  do
  {
    h3 = ((*(h2)).forward);

    ((*(h2)).forward) = h2;
    ((*(h2)).backward) = h2;
    ((*(h2)).parent) = ((void*)0);

    r = ((*(h2)).rank);
    ((void) sizeof ((r < 10000) ? 1 : 0), __extension__ ({ if (r < 10000) ; else __assert_fail ("r < MAX_RANK", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 168, __extension__ __PRETTY_FUNCTION__); }));

    while(hTable[r] != ((void*)0))
    {
      if(LessThan(((*(hTable[r])).item), ((*(h2)).item)))
      {
        AddEntry(hTable[r], h2);
        h2 = hTable[r];
      }
      else
      {
        AddEntry(h2, hTable[r]);
      }
      hTable[r] = ((void*)0);
      r = ((*(h2)).rank);
      ((void) sizeof ((r < 10000) ? 1 : 0), __extension__ ({ if (r < 10000) ; else __assert_fail ("r < MAX_RANK", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 183, __extension__ __PRETTY_FUNCTION__); }));
    }
    hTable[r] = h2;
    if(r > rMax)
    {
      rMax = r;
    }

    h2 = h3;
  }
  while(h2 != h1);




  if(((*(h)).child) != ((void*)0))
  {
    h2 = ((*(h)).child);
    do
    {
      h3 = ((*(h2)).forward);

      ((*(h2)).forward) = h2;
      ((*(h2)).backward) = h2;
      ((*(h2)).parent) = ((void*)0);

      r = ((*(h2)).rank);
      ((void) sizeof ((r < 10000) ? 1 : 0), __extension__ ({ if (r < 10000) ; else __assert_fail ("r < MAX_RANK", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 210, __extension__ __PRETTY_FUNCTION__); }));
      while(hTable[r] != ((void*)0))
      {
        if(LessThan(((*(hTable[r])).item), ((*(h2)).item)))
        {
          AddEntry(hTable[r], h2);
          h2 = hTable[r];
        }
        else
        {
          AddEntry(h2, hTable[r]);
        }
        hTable[r] = ((void*)0);
        r = ((*(h2)).rank);
        ((void) sizeof ((r < 10000) ? 1 : 0), __extension__ ({ if (r < 10000) ; else __assert_fail ("r < MAX_RANK", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 224, __extension__ __PRETTY_FUNCTION__); }));
      }
      hTable[r] = h2;
      if(r > rMax)
      {
        rMax = r;
      }

      h2 = h3;
    }
    while(h2 != ((*(h)).child));
  }





  for(j = 0; j <= rMax; j++)
  {
    if(hTable[j] != ((void*)0))
    {
      break;
    }
  }
  h1 = hTable[j];
  min = h1;
  hTable[j] = ((void*)0);
  j++;
  for(; j <= rMax; j++)
  {
    if(hTable[j] != ((void*)0))
    {
      CombineLists(h1, hTable[j]);
      if(LessThan(((*(hTable[j])).item), ((*(min)).item)))
      {
        min = hTable[j];
      }
      hTable[j] = ((void*)0);
    }
  }

  free<HeapP>(h);

  return(min);
}

       _Ptr<HeapP> DecreaseKey(_Ptr<HeapP> h, _Ptr<HeapP> i, int delta)
{
  ((void) sizeof ((h != ((void*)0)) ? 1 : 0), __extension__ ({ if (h != ((void*)0)) ; else __assert_fail ("h != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 272, __extension__ __PRETTY_FUNCTION__); }));
  ((void) sizeof ((i != ((void*)0)) ? 1 : 0), __extension__ ({ if (i != ((void*)0)) ; else __assert_fail ("i != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 273, __extension__ __PRETTY_FUNCTION__); }));

  if(!(((*(i)).parent) == ((void *)0)))
  {
    RemoveChild(i);
    CombineLists(h, i);
  }
  ((*(i)).item) = Subtract(((*(i)).item), delta);
  if(LessThan(((*(i)).item), ((*(h)).item)))
  {
    return(i);
  }
  else
  {
    return(h);
  }
}




       void
RemoveChild(_Ptr<HeapP> i)
{
  _Ptr<HeapP> parent = 0;

  ((void) sizeof ((i != ((void*)0)) ? 1 : 0), __extension__ ({ if (i != ((void*)0)) ; else __assert_fail ("i != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 299, __extension__ __PRETTY_FUNCTION__); }));

  parent = ((*(i)).parent);

  ((void) sizeof ((parent != ((void*)0)) ? 1 : 0), __extension__ ({ if (parent != ((void*)0)) ; else __assert_fail ("parent != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 303, __extension__ __PRETTY_FUNCTION__); }));

  if((((*(parent)).child) == (i)))
  {
    if(((i) == ((*(i)).forward)))
    {
      ((*(parent)).child) = ((void*)0);
    }
    else
    {
      ((*(parent)).child) = ((*(i)).forward);
    }
  }
  (void)RemoveEntry(i);
  FixRank(parent, ((*(i)).rank) + 1);

  ((*(i)).forward) = i;
  ((*(i)).backward) = i;
  ((*(i)).parent) = ((void*)0);
}

       void
FixRank(_Ptr<HeapP> h, int delta)
{
  ((void) sizeof ((h != ((void*)0)) ? 1 : 0), __extension__ ({ if (h != ((void*)0)) ; else __assert_fail ("h != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 327, __extension__ __PRETTY_FUNCTION__); }));
  ((void) sizeof ((delta > 0) ? 1 : 0), __extension__ ({ if (delta > 0) ; else __assert_fail ("delta > 0", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 328, __extension__ __PRETTY_FUNCTION__); }));

  do
  {
    ((*(h)).rank) = ((*(h)).rank) - delta;
    h = ((*(h)).parent);
  }
  while(h != ((void*)0));
}

       _Ptr<HeapP> Delete(_Ptr<HeapP> h, _Ptr<HeapP> i)
{
  _Ptr<HeapP> h1 = 0;
  _Ptr<HeapP> h2 = 0;

  ((void) sizeof ((h != ((void*)0)) ? 1 : 0), __extension__ ({ if (h != ((void*)0)) ; else __assert_fail ("h != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 343, __extension__ __PRETTY_FUNCTION__); }));
  ((void) sizeof ((i != ((void*)0)) ? 1 : 0), __extension__ ({ if (i != ((void*)0)) ; else __assert_fail ("i != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 344, __extension__ __PRETTY_FUNCTION__); }));

  if(h == i)
  {
    return(DeleteMin(h));
  }

  if((((*(i)).parent) == ((void *)0)))
  {
     (void)RemoveEntry(i);
  }
  else
  {
    RemoveChild(i);
  }
  h1 = ((*(i)).child);
  if(h1 != ((void*)0))
  {
    do
    {
      h2 = ((*(h1)).forward);

      ((*(h1)).forward) = h1;
      ((*(h1)).backward) = h1;
      ((*(h1)).parent) = ((void*)0);

      CombineLists(h, h1);




      if(LessThan(((*(h1)).item), ((*(h)).item)))
      {
        h = h1;
      }

      h1 = h2;
    }
    while(h1 != ((*(i)).child));
  }

  free<HeapP>(i);
  return(h);
}














       void
CombineLists(_Ptr<HeapP> h1, _Ptr<HeapP> h2)
{
  _Ptr<HeapP> h = 0;

  ((void) sizeof (((h1 != ((void*)0)) && (h2 != ((void*)0))) ? 1 : 0), __extension__ ({ if ((h1 != ((void*)0)) && (h2 != ((void*)0))) ; else __assert_fail ("(h1 != NULL) && (h2 != NULL)", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 407, __extension__ __PRETTY_FUNCTION__); }));

  h = h1;

  ((*(((*(h1)).forward))).backward) = h2;
  ((*(((*(h2)).forward))).backward) = h1;
  h = ((*(h1)).forward);
  ((*(h1)).forward) = ((*(h2)).forward);
  ((*(h2)).forward) = h;
}














       void
AddEntry(_Ptr<HeapP> h1, _Ptr<HeapP> h2)
{
  ((void) sizeof (((h1 != ((void*)0)) && (h2 != ((void*)0))) ? 1 : 0), __extension__ ({ if ((h1 != ((void*)0)) && (h2 != ((void*)0))) ; else __assert_fail ("(h1 != NULL) && (h2 != NULL)", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 434, __extension__ __PRETTY_FUNCTION__); }));

  if(((*(h1)).child) == ((void*)0))
  {
    ((*(h1)).child) = h2;
  }
  else
  {
    CombineLists(((*(h1)).child), h2);
  }
  ((*(h2)).parent) = h1;
  ((*(h1)).rank) = ((*(h1)).rank) + ((*(h2)).rank) + 1;
}















       _Ptr<HeapP> RemoveEntry(_Ptr<HeapP> h)
{
  ((void) sizeof ((h != ((void*)0)) ? 1 : 0), __extension__ ({ if (h != ((void*)0)) ; else __assert_fail ("h != NULL", "/home/matt/analyze-conversion/src/Ptrdist/ft/tmp-em-manual/Fheap.c", 464, __extension__ __PRETTY_FUNCTION__); }));

  if(((h) == ((*(h)).forward)))
  {
    return(((*(h)).child));
  }

  ((*(((*(h)).forward))).backward) = ((*(h)).backward);
  ((*(((*(h)).backward))).forward) = ((*(h)).forward);

  return(((*(h)).forward));
}














       _Ptr<HeapP> NewHeap(_Ptr<Item> i)
{
  _Ptr<HeapP> h = 0;

  h = calloc<HeapP>(1, sizeof(HeapP));

  if(h == ((void*)0))
  {
     { (fprintf)(stderr, "Oops, could not malloc\n"); };
    exit(1);
  }
  ((*(h)).item) = i;
  ((*(h)).parent) = ((void*)0);
  ((*(h)).child) = ((void*)0);
  ((*(h)).forward) = h;
  ((*(h)).backward) = h;
  ((*(h)).rank) = 0;
  ((*(h)).marked) = 0;

  return(h);
}

       _Ptr<Item> ItemOf(_Ptr<HeapP> h)
{
  return(((*(h)).item));
}

       _Ptr<HeapP> Find(_Ptr<HeapP> h, _Ptr<Item> item)
{
  _Ptr<HeapP> h1 = 0;
  _Ptr<HeapP> h2 = 0;

  if(h == ((void*)0))
  {
    return(((void*)0));
  }

  h1 = h;
  do
  {
    if(Equal(((*(h1)).item), item))
    {
      return(h1);
    }
    else if(LessThan(((*(h1)).item), item))
    {
      h2 = Find(((*(h1)).child), item);
      if(h2 != ((void*)0))
      {
        return(h2);
      }
    }
    h1 = ((*(h1)).forward);
  }
  while(h1 != h);

  return(((void*)0));
}

