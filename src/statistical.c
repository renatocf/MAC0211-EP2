#include <stdlib.h>
#include <math.h>
#include "statistical.h"

void stat_set_seed(int seed)
{
    srand(seed);
}
/*Acredito que estaja pronto, parece funcionar*/
int stat_gen_uniform(int min, int max)
{
    int k;
    double d;
    d = (double) rand() / ((double) RAND_MAX + 1);
    k = (int) (d * (max - min + 1));
    return (min + k);
}

/*Gera ńúmeros aleatórios de 0 a 1*/
float stat_gen_uniform_float()
{
    float d;
    d = 1.0*rand()/RAND_MAX;
    return d;
}
