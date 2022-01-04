




#ifdef TORONTO
#include <stdio.h>
#define chatting printf
#define PLAIN
#endif

typedef struct tree {
    int val;
    _Ptr<struct tree> left;
    _Ptr<struct tree> right;
} tree_t;

extern _Ptr<tree_t> TreeAlloc (int level, int lo, int hi);
int TreeAdd (_Ptr<tree_t> t);







