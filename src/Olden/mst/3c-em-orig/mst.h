

#include <stdlib.h>
#include "hash.h"
#define MAXPROC 1

#define chatting printf
extern int NumNodes;

struct vert_st {
  int mindist;
  _Array_ptr<struct vert_st> next : count(1);
  Hash edgehash;
};
typedef _Array_ptr<struct vert_st> Vertex;

struct graph_st {
  Vertex vlist _Checked[1];
};
typedef _Ptr<struct graph_st> Graph;

Graph  MakeGraph(int numvert, int numproc);
int dealwithargs(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc));

