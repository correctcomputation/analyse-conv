
#ifdef TORONTO
extern int NumNodes;
#define chatting      printf
#endif

#define NULL 0

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
  struct quad_struct *nw;
  struct quad_struct *ne;
  struct quad_struct *sw;
  struct quad_struct *se;
  struct quad_struct *parent;
#endif

} quad_struct;

typedef quad_struct* QuadTree;


QuadTree MakeTree(int size, int center_x, int center_y, int lo_proc, int hi_proc, QuadTree parent, ChildType ct, int level);










