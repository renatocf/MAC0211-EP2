#include <stdlib.h>
#include <math.h>
#include "statistical.h"

void stat_set_seed(int seed){srand(seed);}

float stat_gen_uniform(int init, int end)
{
    float d;
    d =  1.0*rand()/RAND_MAX;

    return d*(end-init) + init;
}

float stat_gen_gaussian(int init, int end)
{
    float a, b, s;
    do
    {
      a = 2.0*(rand()/RAND_MAX) - 1;
      b = 2.0*(rand()/RAND_MAX) - 1;
      s = a*a + b*b;
    }
    while(s >= 1);

    a = a*sqrt(-2*log(s)/s);
    return (a+1)*((end-init)/2.0) + init;
}

