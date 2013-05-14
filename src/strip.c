#include <stdio.h>
#include <stdlib.h>

#include "strip.h"
#include "utils.h"
#include "terrain.h"
#include "statistical.h"

float prob_island = 0.1; /* Probabilidade de haver uma ilha na linha */

void tstrip_seed  (int seed)
{
    stat_set_seed(seed);
}
void tstrip_island(float prob)
{
    prob_island = prob;
}
void tstrip_free(TStrip strip)
{
    free(strip);
}


TStrip tstrip_generate(int size, int maxl, int maxr,
                       float normalization, TStrip base)
{
    TStrip nova = (TStrip) mallocSafe(size * sizeof(*nova));
    int lmargin, rmargin, i;
    double sum = 0, K;

    if(base == NO_BASE)
    {
        /* Sorteia limites das marges esquerda/direita */
        lmargin = stat_gen_uniform(0, maxl);
        rmargin = stat_gen_uniform(maxr, size-1);

        /* Gera terra na margem esquerda com velocidade 0.
         * A velocidade da água no limite da margem também é 0. */
        for(i = 0; i <= lmargin; i++)
        {
            nova[i].v = 0;
            nova[i].t = LAND;
        }
        nova[i].v = 0;
        nova[i].t = WATER;

        /* Gera terra na margem direita com velocidade 0.
         * A velocidade da água no limite da margem também é 0. */
        /* for(i = rmargin-1; i < size; i++) */
        for(i = size-1; i >= rmargin; i--)
        {
            nova[i].v = 0;
            nova[i].t = LAND;
        }
        nova[i].v = 0;
        nova[i].t = WATER;

        /* Gera água entre os limites de ambas as margens (exceto
         * nas casas laterais, em que v = 0). Vai somando os valores
         * (Ω) para posterior normalização. */
        for(sum = 0, i = lmargin+2; i <= rmargin-2; i++)
        {
            nova[i].v = stat_gen_uniform(0, PI);
            nova[i].t = WATER;
            sum += nova[i].v;
        }

        /* Cria constante de normalização K = Φ/Ω para manter o
         * fluxo desejado constante. */
        K = normalization/sum;
        for(i = lmargin+2; i <= rmargin-2; i++) nova[i].v *= K;
    }
    else /* Temos uma linha base */
    {
        for(i = 0; i<size; i++)
        {
            nova[i].t = ' ';
        }
        /* Busca pela margem esquerda */
        for(i = 0; i < size; i++)
            if(base[i].t != base[i+1].t) break;
        lmargin = i;

        /* Busca pela margem direita */
        for(i = size - 1; i >= 0; i--)                  /* i = size ... i>0 */
            if(base[i].t != base[i-1].t) break;
        rmargin = i;

        /* Se houver duas margens */
        if(lmargin != rmargin)
        {
             int tam_island, pos_island;
             tam_island = 0;
             pos_island = 0;

            if(lmargin+1 < maxl && lmargin>1)
                lmargin += stat_gen_uniform(-1, 1);
            else if(lmargin==1)
                lmargin += stat_gen_uniform(0, 1);
            else
                lmargin += stat_gen_uniform(-1, 0);

            if(rmargin-1>maxr && rmargin < size-2)
                rmargin += stat_gen_uniform(-1, 1);
            else if(rmargin == size - 2)
                rmargin += stat_gen_uniform(-1, 0);
            else
                rmargin += stat_gen_uniform(0, 1);

            /*A ilha deve vir aqui*/
             if(stat_gen_uniform_float() < prob_island)
             {
                 printf("Oieeeeee!! \n");
                 tam_island = (int) stat_gen_gaussian((rmargin - lmargin)/2, 1);
                 pos_island =(int) stat_gen_uniform(lmargin, rmargin - tam_island -1);
                 for(i = pos_island-1; i <= tam_island+pos_island+1; i++)
                 {
                     nova[i].v = 0;
                     if(i == pos_island-1 || i == tam_island+pos_island+1)nova[i].t = WATER;
                     else nova[i].t = LAND;
                 }
             }
            for(i = 0; i < size; i++)
            {
                if((i <= lmargin + 1 || i >= rmargin - 1))
                {
                    nova[i].v = 0;
                    if(i == lmargin+1 || i == rmargin-1)nova[i].t = WATER;
                    else nova[i].t = LAND;
                }
                else if(base[i].t == LAND && nova[i].t != LAND)
                {
                    nova[i].v = stat_gen_uniform(0,PI/4);
                    sum += nova[i].v;
                    nova[i].t = WATER;
                }
                else if(nova[i].t != LAND)
                {
                    nova[i].v = base[i].v + stat_gen_gaussian(0, 1);;
                    sum += nova[i].v;
                    nova[i].t = WATER;
                }
            }
        }
        /*No caso improvavel de só haver uma margem*/
        else printf("problems...");

        K = normalization/sum;
        for(i = lmargin; i < rmargin; i++) nova[i].v *= K;
    }

    return nova;
}

