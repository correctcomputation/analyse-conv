


#include <stdlib.h>
#include "hash.h"
#define MAXPROC 1

#define printf(...)  { (printf)(__VA_ARGS__); }
extern int NumNodes;

struct vert_st {
  int mindist;
  _Ptr<struct vert_st> next;
  Hash edgehash;
};

typedef _Ptr<struct vert_st> Vertex;

struct vert_arr_st {
  _Array_ptr<struct vert_st> block : count(len) ;
  int len;
  _Ptr<struct vert_st> starting_vertex ;
};

typedef struct vert_arr_st VertexArray;

struct graph_st {
  struct vert_arr_st vlist _Checked[1];
};

typedef _Ptr<struct graph_st> Graph;

Graph  MakeGraph(int numvert, int numproc);
int dealwithargs(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc));

void chatting(_Nt_array_ptr<char> str);

