
#include <stdlib.h>

int NumNodes = 1;

int dealwithargs(int argc, char *argv[]) {
  int level;

  if (argc > 1)
    level = atoi(argv[1]);
  else
    level = 64;

  return level;
}
