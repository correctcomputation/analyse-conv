

#include <stdlib.h>
#include "em3d.h"

#ifdef TORONTO
#endif

#ifdef __MINGW32__
#define srand48(x) srand(x)
#define lrand48() (rand() << 16 | rand())
#define drand48() (1.0*rand() / RAND_MAX)
#else
extern double drand48(void);
#endif

static int percentcheck=0,numlocal=0;


void init_random(int seed)
{
  srand48(seed);
}


int gen_number(int range)
{
  return (int)lrand48() % range;
}


int gen_signed_number(int range)
{
  int temp;

  temp = lrand48() % (2*range);
  temp = temp-(range);
  if (temp >= 0) temp++;
  return temp;
}


double gen_uniform_double(void)
{
  return drand48();
}

int check_percent(int percent)
{
  int retval;
  retval=(drand48() < (double) (percent/100.0));
  percentcheck++;
  if (retval) numlocal++;
  return retval;
}

void printstats()
{
   { printf("percentcheck=%d,numlocal=%d\n",percentcheck,numlocal); };
}








