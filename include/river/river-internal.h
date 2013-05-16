#ifndef H_RIVER_INTERNAL_DEFINED
#define H_RIVER_INTERNAL_DEFINED

typedef struct conf Conf;
struct conf
{
    int   length;
    int   height;
    int   left_margin;
    int   right_margin;
    int   freq_island;
    float prob_island;
    float flux;
};

static List river;
static TStrip base;
static Conf Config;

/* Função auxiliar para imprimir
 * a faixa de terra */
static void strip_print (TStrip);

#endif
