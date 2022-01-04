







#include "stdinc.h"
#include <errno.h>

#define A	16807.0
#define M	2147483647.0

void exit(int);




double my_rand(double seed)
{
    double t = 16807.0*seed + 1;
    double floor();


    seed = t - (2147483647.0 * floor(t / 2147483647.0));
    return seed;

}





double xrand(double xl, double xh, double r)
{ double res;

    res = xl + (xh-xl)*r/2147483647.0;
    return (res);
}








error(_Nt_array_ptr<char> msg)
{
    fprintf(stderr, msg);
    if ((*__errno_location ()) != 0)
        perror("Error");
    exit(0);
}



