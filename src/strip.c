#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "utils.h"
#include "terrain.h"
#include "statistical.h"

int seed = 13;

void tstrip_seed(int seed) { stat_set_seed(seed); }

TStrip tstrip_generate(int size, int maxl, int maxr, 
                       float normalization, TStrip base)
{
    TStrip new = (TStrip) mallocSafe(size * sizeof(*new));
    int lmargin, rmargin, i; double sum = 0, K;
    
    if(base == NO_BASE)
    {
        /* Sorteia limites das marges esquerda/direita */
        lmargin = (int) stat_gen_uniform(0, maxl);
        rmargin = (int) stat_gen_uniform(maxr, size-1);
        
        /* Gera terra na margem esquerda com velocidade 0.
         * A velocidade da água no limite da margem também é 0. */
        for(i = 0; i < maxl+1; i++)
            { new[i].v = 0; new[i].t = LAND; }
        new[i].t = WATER;
        
        /* Gera terra na margem direita com velocidade 0.
         * A velocidade da água no limite da margem também é 0. */
        for(i = maxr-1; i < size; i++)
            { new[i].v = 0; new[i].t = LAND; }
        new[maxr-1].t = WATER;
        
        /* Gera água entre os limites de ambas as margens (exceto
         * nas casas laterais, em que v = 0). Vai somando os valores
         * (Ω) para posterior normalização. */
        for(sum = 0, i = maxl+2; i < maxr-2; i++)
            { max[i].v = stat_gen_uniform(0, PI); sum += max[i].v; }
        
        /* Cria constante de normalização K = Φ/Ω para manter o 
         * fluxo desejado constante. */
        K = normalization/sum;
        for(i = maxl+2; i < maxr-2; i++) max[i].v *= K;
    }
    else /* Temos uma linha base */
    {
        /* Busca pela margem esquerda */
        for(i = 0; i < size; i++) 
            if(v[i].t != v[i+1].t) break;
        maxl = i;
        
        /* Busca pela margem direita */
        for(i = size; i > 0; i--) 
            if(v[i].t != v[i-1].t) break;
        maxr = i;
        
        /* Se forem iguais, não há uma margem */
        if(maxl == maxr) printf("problems...");
    }
    
    return new;
}

void tstrip_free(TStrip)
{
}
