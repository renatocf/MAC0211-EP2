#ifndef H_RIVER_DEFINED
#define H_RIVER_DEFINED

/* Funções para configuração de parâmetros */
void river_config_flux        (float);
void river_config_size        (int, int); /* largura/altura */
void river_config_island      (float);    /* probabilidade da ilha */
void river_config_margins     (int, int); /* esquerda/direita */

/* Funções para controle de animação */
void river_animation_generate (int);      /* semente */
void river_animation_iterate  ();
void river_animation_finish   (); 

#endif
