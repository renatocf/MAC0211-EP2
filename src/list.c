#include <stdlib.h>

#include "utils.h"
#include "list-internal.h"

List list_init(int N)
{
    List new = (List) mallocSafe(sizeof(*new));
    new->head = (Link) mallocSafe(sizeof(*new->head));
    new->head->next = new->head;
    new->head->prev = new->head;
    return new;
}

void list_free(List list)
{
    while(!list_empty(list))
        list_remove(list, list->head->next);
    free(list_head(list));
    free(list);
}

int list_empty(List list)
{
    if(list == NULL) return 0;
    if(list->head == list->head->next) return 1;
    return 0;
}

LItem list_remove(List list, Link node)
{
    Link aux;
    LItem item = node->item;
    aux = node->prev;
    aux->next = node->next;
    if(node->next != NULL) node->next->prev = aux;

    free(node);
    return item;
}

void list_insert(List list, LItem item)
{
    Link new = (Link) mallocSafe(sizeof(*new));
    new->item = item;
    new->next = list->head->next;
    new->prev = list->head;
    new->next->prev = new;
    new->prev->next = new;
}

Link  list_head(List list)
{
    return list->head;
}
Link  list_next(Link node)
{
    return node->next;
}
Link  list_prev(Link node)
{
    return node->prev;
}
LItem list_item(Link node)
{
    return node->item;
}

void list_select(List list, int direction, void (*visit) (LItem))
{
    Link aux;
    if(direction == HEAD)
        for(aux = list->head->next; aux != list->head; aux = aux->next)
            visit(aux->item);
    else
        for(aux = list->head->prev; aux != list->head; aux = aux->prev)
            visit(aux->item);
}
