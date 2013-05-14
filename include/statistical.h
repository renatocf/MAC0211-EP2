#ifndef H_STATISTICAL_DEFINED
#define H_STATISTICAL_DEFINED

void  stat_set_seed     (int seed);
int stat_gen_uniform  (int init, int end);
float stat_gen_gaussian (float mean, float stdDev);
float stat_gen_uniform_float();

#endif
