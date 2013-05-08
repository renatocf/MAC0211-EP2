#include<stdio.h>
#include<stdlib.h>

float stat_gen_uniform(int init, int end);
float stat_gen_gaussian(int init, int end);


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

float stat_gen_gaussian(int init, int end)
{
    int i, soma;
    soma = 0;
    for(i = 0; i < 30; i++) soma += (int) stat_gen_uniform(init, end);
    return (float)soma/30;
}
