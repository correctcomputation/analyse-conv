




#ifndef TORONTO
#include <cm/cmmd.h>
#include <fcntl.h>
#endif

#include <stdlib.h>

#ifndef TORONTO

#else
int NumNodes;
#endif

#ifndef TORONTO







#endif

int dealwithargs(int argc, char * * argv )
{
  int level;

  if (argc > 2)
#ifndef TORONTO



#else
    NumNodes = atoi(argv[2]);
  else
    NumNodes = 1;
#endif

  if (argc > 1)
    level = atoi(argv[1]);
  else
    level = 11;

  return level;

}

