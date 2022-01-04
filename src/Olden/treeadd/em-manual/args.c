

#ifndef TORONTO
#include <cm/cmmd.h>
#include <fcntl.h>
#endif
#include <stdlib.h>

#include "tree.h"

#pragma CHECKED_SCOPE ON

#ifdef TORONTO
 int NumNodes;
#else

#endif

#ifndef TORONTO







#endif

int dealwithargs(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc))
{
  int level;

#ifdef TORONTO
  if (argc > 2)
    NumNodes = atoi(argv[2]);
  else
    NumNodes = 4;
#else




#endif

  if (argc > 1)
    level = atoi(argv[1]);
  else
    level = 16;

  return level;
}

