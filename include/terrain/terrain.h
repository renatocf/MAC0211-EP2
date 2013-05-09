#ifndef H_TERRAIN_DEFINED
#define H_TERRAIN_DEFINED

#define LAND  #
#define WATER .

/* Define o tipo TERRENO: um ponto 
 * flutuante que guarda a velocidade
 * daquele trecho do terreno. */
typedef struct _terrain terrain;

char  t_get_type     (terrain);
float t_get_velocity (terrain);

void t_set_type     (terrain, char);
void t_set_velocity (terrain, float);

#endif
