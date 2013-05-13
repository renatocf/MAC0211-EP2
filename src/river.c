/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                              BIBLIOTECAS
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
/* Bibliotecas-padrão */
#include <stdio.h>
#include <stdlib.h>

/* bibliotecas internas */
#include "list.h"
#include "utils.h"
#include "strip.h"
#include "river-internal.h"

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                         FUNÇÕES DE CONFIGURAÇÃO 
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
void river_config_flux   (float flux)          
    { Config.flux = flux; }
void river_config_island (float prob_island) 
    { Config.prob_island = prob_island; }

void river_config_size(int length, int height)
{
    Config.height = height;
    Config.length = length; 
}

void river_config_margins(int left_margin, int right_margin)
{ 
    Config.left_margin = left_margin; 
    Config.right_margin = right_margin; 
}

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                          FUNÇÕES DE ANIMAÇÃO     
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/
void river_animation_generate(int seed)
{
    /** VARIÁVEIS *****************************************************/
        int i = 0;                      /* Contador                  */
        TStrip new_line;                /* Linha gerada              */
        TStrip first_line;              /* 1ª linha gedara           */
        float flux = Config.flux;       /* Fluxo total do rio        */
        int height = Config.height;     /* Altura total do grid      */
        int length = Config.length;     /* Largura total do rio      */
        int maxl = Config.left_margin;  /* Máxima faixa equerda      */
        int maxr = Config.right_margin; /* Máxima faixa direita      */
        
        /* Inicializa semente geradora de faixas de terreno 
         * e cria lista para colocá-las: nosso cenário */ 
        tstrip_seed(seed); river = list_init(height);
    
    /** INICIALIZA RIO ************************************************/
        /* Primeira linha, que servirá de base para todo o rio */
        first_line = tstrip_generate(length, maxl, maxr, flux, NO_BASE);
        
        /* Preenche 'altura' faixas de terreno na lista: */
        list_insert(river, first_line);
        
        for(i = 1, base = first_line; i < height; i++, base = new_line)
        {
            new_line = tstrip_generate(length, maxl, maxr, flux, base);
            list_insert(river, new_line);
        }
        
    /** IMPRIME RIO ***************************************************/
        list_select(river, strip_print);
}

void river_animation_iterate()
{
    /** VARIÁVEIS *****************************************************/
        TStrip top, bottom;
        float flux = Config.flux;       /* Fluxo do rio              */
        int length = Config.length;     /* Largura do grid           */
        int maxl = Config.left_margin;  /* Máxima faixa equerda      */
        int maxr = Config.right_margin; /* Máxima faixa direita      */
        
    /** AVANÇA FAIXA DE TERRENO ***************************************/
        /* Libera linha do topo do grid ('saindo da tela') */
        top = list_remove(river, list_head(river));
        tstrip_free(top); top = NULL;
        
        /* Cria linha da base do grid ('entrando na tela') */
        bottom = tstrip_generate(length, maxl, maxr, flux, base);
        list_insert(river, bottom);
        
    /** IMPRIME RIO ***************************************************/
        list_select(river, strip_print);
}

static void strip_print(TStrip strip)
{
    int i = 0; /* Contador */
    for(i = 0; i < Config.length; i++)
        printf("%c", strip[i].t);
    printf("\n");
}

void river_animation_finish() 
{
    list_free(river);
    river = NULL; base = NULL;
}
