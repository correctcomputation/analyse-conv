




#ifdef TORONTO
extern int NumNodes;
#define chatting      printf
#endif

#ifndef TORONTO
#include <cm/cmmd.h>
#ifdef FUTURES
#include "future-cell.h"
#endif
#include "mem-ref.h"
#endif

typedef enum {black, white, grey} Color;
typedef enum {northwest, northeast, southwest, southeast} ChildType;
typedef enum {north, east, south, west} Direction;


typedef struct quad_struct {
  Color color;
  ChildType childtype;

#ifndef TORONTO





#else
  _Ptr<struct quad_struct> nw;
  _Ptr<struct quad_struct> ne;
  _Ptr<struct quad_struct> sw;
  _Ptr<struct quad_struct> se;
  _Ptr<struct quad_struct> parent;
#endif

} quad_struct;

typedef _Ptr<struct quad_struct> QuadTree;


QuadTree MakeTree(int size, int center_x, int center_y, int lo_proc, int hi_proc, QuadTree parent, ChildType ct, int level);








