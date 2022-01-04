






#include <stdio.h>
#include <stdlib.h>
#include "health.h"

void dealwithargs(int argc, _Array_ptr<_Nt_array_ptr<char>> argv : count(argc)) {
  if (argc < 4) {
    max_level = 3;
    max_time = 15;
    seed = 4;
  } else {
    max_level = atoi(argv[1]);
    max_time = atol(argv[2]);
    seed = atol(argv[3]);
  }

  printf("max_level=%d  max_time=%d  seed=%d \n", max_level, (int)max_time, (int)seed);
}




