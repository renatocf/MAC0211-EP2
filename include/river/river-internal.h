#ifndef H_RIVER_INTERNAL_DEFINED
#define H_RIVER_INTERNAL_DEFINED

typedef struct conf Conf;
struct conf
{
    float flux;
    int   height;
    int   length;
    int   zone;
    float prob_island;
    int   freq_island;
};

static List river;
static TStrip base;
static Conf Config;

/* Função auxiliar para imprimir
 * a faixa de terra */
static void strip_print (TStrip);

#endif
