#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#ifdef TORONTO

#define ALLOC(T, p, sz)      calloc(1, sz)
#define chatting(...)  { printf(__VA_ARGS__); } 
extern int NumNodes, NDim;
#endif

extern int flag;

int dealwithargs(int argc, char * * argv );



struct tree {
  int sz;
  double x,y;
  struct tree * left;
  struct tree * right;
#ifdef TORONTO
  struct tree * next;
  struct tree * prev;
#else

#endif

};

typedef struct tree * Tree;

#ifdef ORDER

#define TREE_SIZE_LOGICAL    1024    
#define NODES_PF_AHEAD       5       
#define TREE_SIZE_PHYSICAL   (TREE_SIZE_LOGICAL + NODES_PF_AHEAD) 


#endif



Tree build_tree(int n,int dir,int lo,int num_proc,double min_x,
                double max_x,double min_y,double max_y);

Tree tsp(Tree t, int sz, int nproc);















