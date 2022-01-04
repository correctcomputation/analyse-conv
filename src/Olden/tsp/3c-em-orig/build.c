













#include <stdio.h>
#include <stdlib.h>

#ifdef TORONTO
#include <math.h>
#ifdef __MINGW32__
#define drand48() (1.0 * rand() / RAND_MAX)
#define srand48(x) srand(x)
#endif
#else




#endif

#define  M_E      2.7182818284590452354
#define  M_E2     7.3890560989306502274
#define  M_E3     20.08553692318766774179
#define M_E6 403.42879349273512264299
#define M_E12 162754.79141900392083592475
#define NULL 0

#include "tsp.h"
#ifdef FUTURES
#include "future-cell.h"
#endif


static double median(double min,double max,int n);
static double uniform(double min, double max);


static double median(double min,double max,int n) {
  double t;
  double retval;

  t = drand48();
  if (t>0.5) {
    retval=log(1.0-(2.0*(162754.79141900392083592475 -1)*(t-0.5)/162754.79141900392083592475))/12.0;
    }
  else {
    retval=-log(1.0-(2.0*(162754.79141900392083592475 -1)*t/162754.79141900392083592475))/12.0;
    }

  retval = (retval+1.0) * (max-min)/2.0;
  retval = retval + min;
  return retval;
}


static double uniform(double min, double max) {
  double retval;

  retval = drand48();
  retval = retval * (max-min);
  return retval + min;
}



Tree  build_tree(int n,int dir,int lo,int num_proc,double min_x,
                double max_x,double min_y,double max_y) {
  double med;
  Tree t = ((void *)0);
#ifdef FUTURES

#endif

  if (n==0) return 0;

  t = (_Ptr<struct tree>) malloc<struct tree>(sizeof(*t));

  if (dir) {
    dir = !dir;
    med = median(min_x,max_x,n);
#ifndef FUTURES
    t->left=build_tree(n/2,dir,lo+num_proc/2,num_proc/2,min_x,med,min_y,max_y);
    t->right=build_tree(n/2,dir,lo,num_proc/2,med,max_x,min_y,max_y);
#else



#endif
    t->x = med;
    t->y = uniform(min_y,max_y);
    }
  else {
    dir = !dir;
    med = median(min_y,max_y,n);
#ifndef FUTURES
    t->left=build_tree(n/2,dir,lo+num_proc/2,num_proc/2,min_x,max_x,min_y,med);
    t->right=build_tree(n/2,dir,lo,num_proc/2,min_x,max_x,med,max_y);
#else



#endif
    t->y = med;
    t->x = uniform(min_x,max_x);
    }
  t->sz = n;
  t->next = 0;
  t->prev = 0;
#ifdef FUTURES


#endif
  return t;
}




