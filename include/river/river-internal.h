#ifndef H_RIVER_INTERNAL_DEFINED
#define H_RIVER_INTERNAL_DEFINED

typedef struct conf Conf;
struct conf {
    int   length;
    int   height;
    int   left_margin;
    int   right_margin;
    float flux;
};

static Conf Config;
static List river; 
static TStrip base;

#endif
