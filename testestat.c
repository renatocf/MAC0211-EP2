#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float stat_gen_uniform(int init, int end);
float stat_gen_gaussian(int init, int end);


int main(int argc, char*argv[])
{
    int i, init, end;
    init = atoi(argv[1]);
    end = atoi(argv[2]);
    for(i=0;i<30;i++)
        printf("%f\n",stat_gen_gaussian(init, end));
    return 0;
}


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
      a = 2.0*rand()/RAND_MAX - 1;
      b = 2.0*rand()/RAND_MAX - 1;
      s = a*a + b*b;
    }
    while(s >= 1);

    a = a*sqrt(-2*log(s)/s);
    printf("%d/n", a);
    return (a+1)*((end-init)/2.0) + init;
}

