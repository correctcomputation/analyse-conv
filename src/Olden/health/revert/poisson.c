





#include <stdio.h>
#include <math.h>
#include "health.h"

float my_rand(long long idum)
{
  long long k;
  float answer;

  idum ^= 123459876;
  k = idum / 127773;
  idum = 16807 * (idum - k * 127773) - 2836 * k;
  idum ^= 123459876;
  if (idum < 0)
    idum += 2147483647;
  answer = (1.0 / 2147483647) * idum;
  return answer;
}






