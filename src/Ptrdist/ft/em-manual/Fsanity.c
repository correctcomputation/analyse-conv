





























#include <stdio.h>
#include "Fheap.h"
#include "Fstruct.h"
#include "Fsanity.h"

#pragma CHECKED_SCOPE ON

int
SanityCheck1(_Ptr<HeapP> h, _Ptr<Item> i)
{
  _Ptr<HeapP> h1 = 0;

  if(h == ((void *)0))
  {
     return(1);
  }

  h1 = h;
  do
  {
    if(LessThan(((*(h1)).item), i))
    {
      return(0);
    }
    if(!SanityCheck1(((*(h1)).child), ((*(h1)).item)))
    {
      return(0);
    }

    h1 = ((*(h1)).forward);
  }
  while(h1 != h);

  return(1);
}

int
SanityCheck2(_Ptr<HeapP> h)
{
  int sum;
  _Ptr<HeapP> h1 = 0;
  _Ptr<HeapP> h2 = 0;

  if(h == ((void *)0))
  {
     return(1);
  }

  h1 = h;
  do
  {
    if(((*(h1)).child) != ((void *)0))
    {
      sum = 0;
      h2 = ((*(h1)).child);
      do
      {
         sum += ((*(h2)).rank) + 1;

         h2 = ((*(h2)).forward);
      }
      while(h2 != ((*(h1)).child));
      if(sum != ((*(h1)).rank))
      {
        return(0);
      }

      if(!SanityCheck2(((*(h1)).child)))
      {
        return(0);
      }
    }

    h1 = ((*(h1)).forward);
  }
  while(h1 != h);

  return(1);
}

int
SanityCheck3(_Ptr<HeapP> h, int rank)
{
  int sum;
  _Ptr<HeapP> h1 = 0;
  _Ptr<HeapP> h2 = 0;

  if((h == ((void *)0)) && (rank == 0))
  {
     return(1);
  }

  sum = 0;
  h1 = h;
  do
  {
    sum += ((*(h1)).rank) + 1;

    if(!SanityCheck3(((*(h1)).child), ((*(h1)).rank)))
    {
      return(0);
    }

    h1 = ((*(h1)).forward);
  }
  while(h1 != h);

  if(sum == rank)
  {
    return(1);
  }
  else
  {
    return(0);
  }
}

void
PrettyPrint(_Ptr<HeapP> h)
{
  _Ptr<HeapP> h1 = 0;

  if(h == ((void *)0))
  {
    _Unchecked { (printf)(" nil "); };
    return;
  }

  _Unchecked { (printf)("("); };

  h1 = h;
  do
  {

    _Unchecked { (printf)("[%u] ", ((*(h1)).rank)); };
    PrettyPrint(((*(h1)).child));
    h1 = ((*(h1)).forward);
  }
  while(h1 != h);

  _Unchecked { (printf)(")"); };
}

#pragma CHECKED_SCOPE OFF
