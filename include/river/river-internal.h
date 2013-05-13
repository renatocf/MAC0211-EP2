#ifndef H_RIVER_INTERNAL_DEFINED
#define H_RIVER_INTERNAL_DEFINED

typedef struct conf Conf;
struct conf {
    int   length;
    int   height;
    int   left_margin;
    int   right_margin;
    float prob_island;
    float flux;
};

static Conf Config;
static List river; 
static TStrip base;

/* Função auxiliar para imprimir
 * a faixa de terra */
static void strip_print (TStrip);

#endif
