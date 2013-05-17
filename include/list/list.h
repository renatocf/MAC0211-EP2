#ifndef H_LIST_DEFINED
#define H_LIST_DEFINED

#include "list-item.h"

#define HEAD 1
#define TAIL 0

/* Tipos para lista e nódulo */
typedef struct list *List;
typedef struct lnode *Link;

/* Funções para uso do cliente */
List  list_init   (int);
Link  list_head   (List);
Link  list_next   (Link);
Link  list_prev   (Link);
LItem list_item   (Link);
void  list_free   (List);
int   list_empty  (List);
LItem list_remove (List, Link);
void  list_insert (List, LItem);
void  list_select (List, int direction, void (*visit) (LItem));

#endif
