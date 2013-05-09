#include <stdlib.h>
#include <math.h>
#include "statistical.h"

void stat_set_seed(int seed){srand(seed);}
/*Acredito que estaja pronto, parece funcionar*/
float stat_gen_uniform(int init, int end)
{
    float d;
    d =  1.0*rand()/RAND_MAX;

    return d*(end-init) + init;
}

float stat_gen_gaussian(float mean, float stdDev)
{
    float u, v, s, mul;
    do
    {
    u = 2.0*rand()/RAND_MAX - 1;
    v = 2.0*rand()/RAND_MAX - 1;
    s = u * u + v * v;
    } while (s >= 1 || s == 0);
    mul = sqrt(-2.0*log(s)/s);

    return mean + stdDev * u * mul;
}
