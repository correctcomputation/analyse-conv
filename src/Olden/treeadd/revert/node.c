



#ifndef TORONTO
#include <cm/cmmd.h>
#endif

#ifdef FUTURES
#include "future-cell.h"
#endif

#ifndef TORONTO
#include "mem-ref.h"
#endif

#include <stdlib.h>
#include "tree.h"


#ifdef TORONTO
extern int NumNodes;
#endif

int dealwithargs(int argc, char * * argv );

typedef struct {
    long level;
} startmsg_t;

int main (int argc, char * * argv )
{
    tree_t * root = ((void*)0);
    int level,result;

#ifdef FUTURES

#else
#ifndef TORONTO

#endif
    level = dealwithargs(argc, argv);
#endif
#ifndef TORONTO


#endif
#ifdef TORONTO
     { printf("Treeadd with %d levels on %d processors \n", level, NumNodes); };

#else


#endif

     { printf("About to enter TreeAlloc\n"); };
#ifndef TORONTO

#endif

#ifdef TORONTO
    root = TreeAlloc (level, 0, NumNodes);
#else

#endif

#ifndef TORONTO

#endif
     { printf("About to enter TreeAdd\n"); };

#ifndef PLAIN

#endif
#ifndef TORONTO

#endif
{ int i; for (i = 0; i < 100; ++i)
    result = TreeAdd (root);
}
#ifndef TORONTO

#endif
     { printf("Received result of %d\n",result); };

#ifndef TORONTO


#endif

#ifdef FUTURES

#endif
    exit(0);

}



int TreeAdd (tree_t * t)
{
  if (t == ((void*)0)) {
    return 0;
  }
  else {
#ifdef FUTURES    


















#else
    int leftval;
    int rightval;
    tree_t * tleft = ((void*)0);
    tree_t * tright = ((void*)0);
    int value;

    tleft = t->left;
    leftval = TreeAdd(tleft);
    tright = t->right;
    rightval = TreeAdd(tright);

    value = t->val;


    return leftval + rightval + value;
#endif
  }
}



