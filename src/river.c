#include "list.h"
#include "utils.h"
#include "strip.h"

typedef struct config Config
static struct config {
    int length;
    int height;
    int left_margin;
    int right_margin;
    int flux;
}

static List river; 
static TStrip base;
/*
----+----1----+----2----+----3----+----4----+----5----+----6----+----7--
*/
void river_config_flux(int flux) { Config.flux = flux; }

void river_config_size(int length, int height)
{
    Config.height = heigh; 
    Config.length = length; 
}

void river_config_margins(int left_margin, int right_margin)
{ 
    Config.left_margin = left_margin; 
    Config.right_margin = right_margin; 
}

void river_animation_generate(int seed)
{
    /** VARIÁVEIS *****************************************************/
        int i = 0;                      /* Contador                  */
        int height = Config.height;     /* Altura do grid            */
        int length = Config.length;     /* Largura do grid           */
        TStrip first_line, new_line;    /* Terrenos referência       */
        int maxl = Config.left_margin;  /* Máxima faixa equerda      */
        int maxr = Config.right_margin; /* Máxima faixa direita      */
        
        /* Inicializa semente geradora de faixas de terreno 
         * e cria lista para colocá-las: nosso cenário */ 
        tstrip_seed(seed); river = list_init(height);
    
    /** INICIALIZA RIO ************************************************/
        /* Primeira linha, que servirá de base para todo o rio */
        first_line = strip_generate(length, maxl, maxr, flux, NO_BASE);
        
        /* Preenche 'altura' faixs de terreno na lista: */
        list_insert(river, first_line);
        for(i = 1, base = first_line; i < height; i++, base = new_line)
        {
            new_line = strip_generate(length, maxl, maxr, flux, base);
            list_insert(river, new_line);
        }
        
    /** IMPRIME RIO ***************************************************/
        list_select(river, strip_print);
}

void river_animation_iterate()
{
    /** VARIÁVEIS *****************************************************/
        TStrip top, bottom;
        int height = Config.height;     /* Altura do grid            */
        int length = Config.length;     /* Largura do grid           */
        int maxl = Config.left_margin;  /* Máxima faixa equerda      */
        int maxr = Config.right_margin; /* Máxima faixa direita      */
        TStrip top, bottom;
        
    /** AVANÇA FAIXA DE TERRENO ***************************************/
        /* Libera linha do topo do grid ('saindo da tela') */
        top = list_remove(river, list_head(river));
        tstrip_free(top); top = NULL;
        
        /* Cria linha da base do grid ('entrando na tela') */
        bottom = strip_generate(length, maxl, maxr, flux, base);
        list_insert(river, bottom);
        
    /** IMPRIME RIO ***************************************************/
        list_select(river, tstrip_print)
}

void river_animation_finish() 
{
    list_free(river);
    river = NULL; base = NULL;
}
