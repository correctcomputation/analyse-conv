#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#pragma CHECKED_SCOPE ON

#ifdef TORONTO

#define ALLOC(T, p, sz)      calloc<T>(1, sz)
#define chatting(...) _Unchecked { printf(__VA_ARGS__); } 
extern int NumNodes, NDim;
#endif

extern int flag;

int dealwithargs(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc));



struct tree {
  int sz;
  double x,y;
  _Ptr<struct tree> left;
  _Ptr<struct tree> right;
#ifdef TORONTO
  _Ptr<struct tree> next;
  _Ptr<struct tree> prev;
#else

#endif

};

typedef _Ptr<struct tree> Tree;

#ifdef ORDER

#define TREE_SIZE_LOGICAL    1024    
#define NODES_PF_AHEAD       5       
#define TREE_SIZE_PHYSICAL   (TREE_SIZE_LOGICAL + NODES_PF_AHEAD) 


#endif



Tree build_tree(int n,int dir,int lo,int num_proc,double min_x,
                double max_x,double min_y,double max_y);

Tree tsp(Tree t, int sz, int nproc);















#pragma CHECKED_SCOPE OFF
