#include "terrain-internal.h"

/* Getters para um 'pixel' de terreno: */
char  t_get_type     (terrain T) { return T.t; }
float t_get_velocity (terrain T) { return T.v; }

void t_set_type     (terrain T, char t)  { T.t = t; }
void t_set_velocity (terrain T, float v) { T.v = v; }
