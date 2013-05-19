/***************************************************/
/**  MAC 0211  -  Laboratório de Programação I    **/
/**  IME-USP   -  Primeiro  Semestre  de    2013  **/
/**  Turma 45  -  Kelly Rosa Bragheto             **/
/**                                               **/
/**  Segundo   Exercício-Programa                 **/
/**  Arquivo:  river.c                            **/
/**                                               **/
/**  Karina Suemi Awoki                  7572102  **/
/**  Renato Cordeiro Ferreira            7990933  **/
/**  Ruan de Menezes Costa               7990929  **/
/**                                               **/
/**  Em caso de eventuais problemas, acesse:      **/
/**  git@github.com:renatocf/MAC0211-EP2.git      **/
/***************************************************/ 

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
{
    Config.flux = flux;
}

void river_config_island (float prob_island, int freq_island)
{
    Config.prob_island = prob_island;
    Config.freq_island = freq_island;
}

void river_config_size(int length, int height)
{
    Config.height = height;
    Config.length = length;
}

void river_config_margins(int zone)
{
    Config.zone = zone;
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
        int i = 0;                       /* Contador                 */
        Link new_node;                   /* Novo nódulo              */
        TStrip new_line;                 /* Linha gerada             */
        TStrip first_line;               /* 1ª linha gedara          */
        int zone = Config.zone;          /* 'Zona de conforto'       */
        float flux = Config.flux;        /* Fluxo total do rio       */
        int height = Config.height;      /* Altura total do grid     */
        int length = Config.length;      /* Largura total do rio     */
        int freq = Config.freq_island;   /* Distância entre ilhas    */
        float prob = Config.prob_island; /* Probabilidade de ilhas   */

        base = (TStrip) mallocSafe(length * sizeof(*base));
        
        /* Inicializa semente geradora de faixas de terreno
         * e cria lista para colocá-las: nosso cenário */
        tstrip_seed(seed); tstrip_island(prob, freq);
        river = list_init(height);

    /** INICIALIZA RIO ************************************************/
        /* Primeira linha, que servirá de base para todo o rio */
        first_line = tstrip_generate(length, zone, flux, NO_BASE, NULL);
        new_node = list_new_node(first_line);
        
        /* Preenche 'altura' faixas de terreno na lista: */
        list_insert(river, new_node);
        
        save_base(first_line); /* Primeira linha será a primeira base*/
        for(i = 1; i < height; i++, save_base(new_line))
        {
            new_line = tstrip_generate(length, zone, flux, base, NULL);
            new_node = list_new_node(new_line);
            list_insert(river, new_node);
        }
        
    /** IMPRIME RIO ***************************************************/
        list_select(river, HEAD, strip_print);
}

void river_animation_iterate()
{
    /** VARIÁVEIS *****************************************************/
        TStrip top;                 /* Auxiliar para inserção de     */
        Link new_node;              /* Novo nódulo 'criado'          */
        TStrip new_item;            /* Item do novo nódulo           */
        int zone = Config.zone;     /* 'Zona de conforto'            */
        float flux = Config.flux;   /* Fluxo do rio (Σv)             */
        int length = Config.length; /* Largura do grid               */

    /** AVANÇA FAIXA DE TERRENO ***************************************/
        /* Libera linha do topo do grid ('saindo da tela') */
        new_node = list_prev(list_head(river));
        list_remove(river, new_node);
        
        /* Cria linha da base do grid ('entrando na tela') */
        new_item = list_item(new_node);
        top = tstrip_generate(length, zone, flux, base, new_item);
        save_base(top); list_insert(river, new_node);
        
    /** IMPRIME RIO ***************************************************/
        list_select(river, HEAD, strip_print);
}

/* Encerra animação e libera toda a memória */
void river_animation_finish()
{
    list_free(river); free(base);
    river = NULL; base = NULL;
}

/*
////////////////////////////////////////////////////////////////////////
-----------------------------------------------------------------------
                           FUNÇÕES AUXILIARES 
-----------------------------------------------------------------------
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

void save_base(TStrip strip)
{
    int i = 0;
    for(i = 0; i < Config.length; i++)
        { base[i].t = strip[i].t; base[i].v = strip[i].v; }
    printf("\n");
}

/* Função auxiliar para imprimir a estrutura do item */
void strip_print(TStrip strip)
{
    int i = 0; /* Contador */
    for(i = 0; i < Config.length; i++)
        printf("%c", strip[i].t);
    printf("\n");
}
