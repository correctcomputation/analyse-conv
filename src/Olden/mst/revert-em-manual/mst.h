


#include <stdlib.h>
#include "hash.h"
#define MAXPROC 1

#define printf(...)  { (printf)(__VA_ARGS__); }
extern int NumNodes;

struct vert_st {
  int mindist;
  struct vert_st * next;
  Hash edgehash;
};

typedef struct vert_st * Vertex;

struct vert_arr_st {
  struct vert_st * block ;
  int len;
  struct vert_st * starting_vertex ;
};

typedef struct vert_arr_st VertexArray;

struct graph_st {
  struct vert_arr_st vlist [1];
};

typedef struct graph_st * Graph;

Graph MakeGraph(int numvert, int numproc);
int dealwithargs(int argc, char * * argv );

void chatting(char * str);

