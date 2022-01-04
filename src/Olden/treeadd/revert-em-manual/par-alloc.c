




#ifndef TORONTO
#include "mem-ref.h"
#include "future-cell.h"
#endif

#include "tree.h"


tree_t * TreeAlloc (int level, int lo, int proc) {
  if (level == 0)
    return ((void*)0);
  else {
    tree_t * new = ((void*)0);
    tree_t * right = ((void*)0);
    tree_t * left = ((void*)0);
    new = calloc(1, sizeof(tree_t));
    left = TreeAlloc(level -1, lo+proc/2, proc/2);
    right=TreeAlloc(level-1,lo,proc/2);
    new->val = 1;
    new->left = left;
    new->right = right;
    return new;
  }
}
