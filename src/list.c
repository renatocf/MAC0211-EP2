#include <stdlib.h>

#include "list-internal.h"
#include "utils.h"

List list_init(int N)
{
    List new = (List) mallocSafe(sizeof(*new));
    new->head = (Link) mallocSafe(sizeof(*new->head));
    new->head->next = new->head;
    return new;
}

void list_free(List list)
{
    while(!list_empty(list))
        list_remove(list, list->head);
    free(list->head); free(list);
}

int list_empty(List list)
{
    if(list->head == list->head->next) return 1;
    return 0;
}

LItem list_remove(List list, Link node)
{
    LItem item = node->next->item;
    Link dead = node->next;
    
    node->next = dead->next;
    free(dead); dead = NULL;
    return item;
}

void list_insert(List list, LItem item)
{
    Link new = (Link) mallocSafe(sizeof(*new));
    new->item = item; new->next = list->head->next;
    list->head->next = new;
}

Link list_head(List list) { return list->head; }
Link list_next(Link node) { return node->next; }

void list_select(List list, void (*visit) (LItem))
{
    Link aux;
    for(aux = list->head->next; aux != list->head; aux = aux->next)
        visit(aux->item);
}
