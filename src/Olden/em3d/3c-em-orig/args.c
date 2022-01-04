

#include "em3d.h"

#ifndef TORONTO
#include <cm/cmmd.h>
#include <fcntl.h>
#endif

#ifdef TORONTO
int NumNodes;
#else
#ifdef OLDEN

#endif
#endif

extern int DebugFlag;

#ifndef TORONTO







#endif

void dealwithargs(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc))
{
#ifdef TORONTO
  if (argc > 4)
    NumNodes = atoi(argv[4]);
  else
    NumNodes = 1;
#else
#ifdef OLDEN








#endif
#endif

  if (argc > 1)
    n_nodes = atoi(argv[1]);
  else
    n_nodes = 64;

  if (argc > 2)
    d_nodes = atoi(argv[2]);
  else
    d_nodes = 3;

  if (argc > 3)
    local_p = atoi(argv[3]);
  else
    local_p = 75;
}


