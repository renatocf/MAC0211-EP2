#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float stat_gen_uniform(int init, int end);
float stat_gen_gaussian(float mean, float stdDev);


int main(int argc, char*argv[])
{
    int i, init, end;
    init = atoi(argv[1]);
    end = atoi(argv[2]);
    for(i=0;i<30;i++)
        printf("%f\n",stat_gen_uniform(init, end));
    return 0;
}


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
