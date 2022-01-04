




#ifndef TORONTO
#include "mem-ref.h"
#include "future-cell.h"
#endif

#include "tree.h"
extern void *malloc(unsigned);

_Ptr<tree_t> TreeAlloc (int level, int lo, int proc) {
  if (level == 0)
    return ((void*)0);
  else {
    _Ptr<struct tree> new = ((void *)0);
    _Ptr<struct tree> right = ((void *)0);
    _Ptr<struct tree> left = ((void *)0);
    new = (_Ptr<struct tree>) malloc<struct tree>(sizeof(tree_t));
    left = TreeAlloc(level -1, lo+proc/2, proc/2);
    right=TreeAlloc(level-1,lo,proc/2);
    new->val = 1;
    new->left = (_Ptr<struct tree>) left;
    new->right = (_Ptr<struct tree>) right;
    return new;
  }
}
