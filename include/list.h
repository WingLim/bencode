//
// Created by WingLim on 2020/12/21.
//

#ifndef CDATASTRUCTURES_LIST_H
#define CDATASTRUCTURES_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct node {
    struct node *next;
    size_t size;
    unsigned char data[];
} node_t;

typedef struct list {
    node_t *head;
    node_t *tail;
    unsigned size;
} list_t;

list_t          *list_init(void);
void            list_free(list_t *list);
int             list_add(list_t *list, unsigned char *data, size_t size);
int             list_remove(list_t *list, unsigned char *data);
bool            list_contains(list_t *list, unsigned char *data);

void            *list_iter_first(list_t *list);
void            *list_iter_next(void *iter);
unsigned char   *list_iter_get_value(void *iter);

#define FOREACH_NODE(_node, _list_ptr) \
    for(void *_iter = list_iter_first(_list_ptr); \
        _iter && (_node = list_iter_get_value(_iter)); _iter = list_iter_next(_iter))

#endif //CDATASTRUCTURES_LIST_H
