#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "strip.h"
#include "utils.h"
#include "terrain.h"
#include "statistical.h"

float prob_island; /* Probabilidade de haver uma ilha na linha */
int freq_island;
int j = 0;

void tstrip_seed  (int seed)
{
    stat_set_seed(seed);
}
void tstrip_island(float prob, int freq)
{
    freq_island = freq;
    prob_island = prob;
}
void tstrip_free(TStrip strip)
{
    free(strip);
}


TStrip tstrip_generate(int size, int zone,
                       float normalization, TStrip base)
{
    TStrip nova = (TStrip) mallocSafe(size * sizeof(*nova));
    int lmargin, rmargin, maxl, maxr, i;
    float sum = 0, K;

    maxl = stat_gen_uniform(1, size-zone-1);
    maxr = maxl + zone;

    if(base == NO_BASE)
    {
        /* Sorteia limites das marges esquerda/direita */
        lmargin = stat_gen_uniform(0, maxl);
        rmargin = stat_gen_uniform(maxr, size-1);

        /* Gera terra na margem esquerda com velocidade 0.*/
        for(i = 0; i <= lmargin; i++)
        {
            nova[i].v = 0;
            nova[i].t = LAND;
        }

        /* Gera terra na margem direita com velocidade 0.*/
        for(i = size-1; i >= rmargin; i--)
        {
            nova[i].v = 0;
            nova[i].t = LAND;
        }
        /* Gera água entre os limites de ambas as margens (exceto
         * nas casas laterais, em que v = 0). Vai somando os valores
         * (Ω) para posterior normalização. */

        for(i = 1; i < size-1; i++)
        {
            nova[i].t = WATER;
            nova[i].v = stat_gen_uniform(0, PI);
            sum += nova[i].v;
        }
        nova[lmargin+1].v = 0;
        nova[rmargin-1].v = 0;

        /* Cria constante de normalização K = Φ/Ω para manter o
         * fluxo desejado constante. */
        K = normalization/sum;
        for(i = lmargin+2; i <= rmargin-2; i++) nova[i].v *= K;
    }
    else /* Temos uma linha base */
    {
        int tam_island = 0, pos_island = 0;

        /* Limpa a linha */
        for(i = 0; i < size; i++) nova[i].t = ' ';

        /* Busca pela margem esquerda */
        for(i = 0; i < size; i++)
            if(base[i].t != base[i+1].t) break;
        lmargin = i;
        /* Busca pela margem direita */
        for(i = size - 1; i >= 0; i--)
            if(base[i].t != base[i-1].t) break;
        rmargin = i;


        if(maxl == 0);
        else if(lmargin < maxl && lmargin > 0)
            lmargin += stat_gen_uniform(-1, 1);
        else if(lmargin==0)
            lmargin += stat_gen_uniform(0, 1);
        else
            lmargin += stat_gen_uniform(-1, 0);

        if(size-1 == maxr);
        else if(rmargin>maxr && rmargin < size-1)
            rmargin += stat_gen_uniform(-1, 1);
        else if(rmargin == size - 1)
            rmargin += stat_gen_uniform(-1, 0);
        else
            rmargin += stat_gen_uniform(0, 1);

        /* A ilha vem aqui */
        if(j != freq_island)j++;
        else
        {
            j = 0;
            if(stat_gen_uniform_float() < prob_island)
            {
                j = 0;
                tam_island = stat_gen_uniform(1, (rmargin - lmargin)/2.0);
                pos_island = stat_gen_uniform(lmargin+1, rmargin - tam_island -1);

                for(i = pos_island-1; i <= pos_island+tam_island+1; i++)
                {
                    nova[i].v = 0;
                    if(i == pos_island-1 || i == tam_island+pos_island+1)nova[i].t = WATER;
                    else nova[i].t = LAND;
                }

            }
        }

        for(i = 0; i < size; i++)
        {
            if(i <= lmargin + 1 || i >= rmargin - 1)
            {
                nova[i].v = 0;
                if(i == lmargin+1 || i == rmargin-1)nova[i].t = WATER;
                else nova[i].t = LAND;
            }
            else if(base[i].t == LAND && nova[i].t != LAND)
            {
                nova[i].v = stat_gen_uniform(0,PI/4.0);
                sum += nova[i].v;
                nova[i].t = WATER;
            }
            else if(nova[i].t != LAND)
            {
                nova[i].v = base[i].v + abs(stat_gen_gaussian(0, 1));
                sum += nova[i].v;
                nova[i].t = WATER;
            }
        }

        if(sum != 0) K = normalization/sum;
        else K = 0;
        for(i = lmargin; i <= rmargin; i++) (nova[i].v) *= K;
    }

    return nova;
}

