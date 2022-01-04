











#ifndef FILE
#ifdef TORONTO
#include <stdio.h>
#else
#  include "stdio.h"
#endif
#endif

#include <math.h>
#include <stdlib.h>

#pragma CHECKED_SCOPE ON





typedef _Ptr<FILE> stream;





#ifndef NULL
#  define NULL 0
#endif





typedef short int bool;

#define FALSE 0
#define TRUE  1






typedef unsigned char byte;





typedef _Nt_array_ptr<char> string;






#ifndef  SINGLEPREC
  typedef double real;
  typedef _Ptr<double> realptr;
#else


#endif







#ifndef TORONTO
#define void int
#endif






typedef _Ptr<void()> proc;
typedef _Ptr<int()> iproc;
typedef _Ptr<real()> rproc;






#define private     static
#define permanent static





#define streq(x,y) (strcmp((x), (y)) == 0)





#define   PI         3.14159265358979323846
#define   TWO_PI     6.28318530717958647693
#define   FOUR_PI   12.56637061435917295385
#define   HALF_PI    1.57079632679489661923
#define   FRTHRD_PI  4.18879020478639098462







#define   ABS(x)       (((x) < 0) ? -(x) : (x))
#define   MAX(x,y)     (((x) > (y)) ? (x) : (y))
#define   MIN(x,y)     (((x) < (y)) ? (x) : (y))

#pragma CHECKED_SCOPE OFF
