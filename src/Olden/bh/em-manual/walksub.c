#define global 
#include "defs.h"

#pragma CHECKED_SCOPE ON

typedef struct {
  bodyptr pskip;
  vector pos0;
  real phi0;
  vector acc0;
} hgstruct;
typedef _Ptr<struct hgstruct> hgsptr;






extern bool subdivp(nodeptr p, real dsq, real tolsq, hgstruct hg);
hgstruct walksub(nodeptr p, real dsq, real tolsq, hgstruct hg, int level);
hgstruct gravsub(nodeptr p, hgstruct hg);

hgstruct walksub(nodeptr p, real dsq, real tolsq, hgstruct hg, int level)
{
  register int k, i;
  register nodeptr r = ((void*)0);
  nodeptr tmp _Checked[(1 << 3)] = {0};


  if (subdivp(p, dsq, tolsq, hg)) {
    for (k = 0; k < (1 << 3); k++) {
      _Unchecked { r = ((_Assume_bounds_cast<cellptr>(p))->subp)[k];}
      if (r != ((void*)0))
 hg = walksub(r, dsq / 4.0, tolsq, hg, level+1);
    }
  }
  else if (p != (nodeptr) hg.pskip) {
    hg = gravsub(p, hg);
  }


  return hg;
}




