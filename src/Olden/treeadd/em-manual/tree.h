




#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#pragma CHECKED_SCOPE ON

#ifdef TORONTO
#define chatting(...) _Unchecked { printf(__VA_ARGS__); }
#define PLAIN
#endif

typedef struct tree {
    int val;
    _Ptr<struct tree> left;
    _Ptr<struct tree> right;
} tree_t;

extern _Ptr<tree_t> TreeAlloc(int level, int lo, int hi);
int TreeAdd (_Ptr<tree_t> t);






#pragma CHECKED_SCOPE OFF
