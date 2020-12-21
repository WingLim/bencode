//
// Created by WingLim on 2020/12/21.
//
#include <stdlib.h>
#include <string.h>

#include "list.h"

static node_t *node_init(void *data, size_t size) {
    node_t *node = malloc(sizeof(node_t) + size);
    if (node) {
        node->next = NULL;
        node->size = size;
        memcpy(node->data, data, size);
    }
    return node;
}

static void node_free(node_t *node) {
    free(node);
}

list_t *list_init(void) {
    list_t *l = malloc(sizeof(list_t));
    if (l) {
        l->head = NULL;
        l->size = 0;
    }
    return l;
}

void list_free(list_t *list) {
    node_t *curr = list->head;
    while (curr) {
        node_t *tmp = curr->next;
        node_free(curr);
        curr = tmp;
    }
    free(list);
}

int list_add(list_t *list, unsigned char *data, size_t size) {
    node_t *new_node;
    new_node = node_init(data, size);
    if (!new_node) {
        return -1;
    }

    if (!list->head) {
        list->head = new_node;
        list->size = 1;
        list->tail = new_node;
        return 0;
    }

    list->tail->next = new_node;
}
int list_remove(list_t *list, unsigned char *data) {
    if (!list->head) {
        return -1;
    }

    for (node_t *curr = list->head, *prev = NULL; curr; prev = curr, curr = curr->next) {
        if (memcmp(curr->data, data, curr->size)) {
            continue;
        }
        if (prev) {
            prev->next = curr->next;
        } else {
            list->head = curr->next;
        }
        if (list->tail == curr) {
            list->tail = prev;
        }
        node_free(curr);
        list->size--;
        return 0;
    }
}

bool list_contains(list_t *list, unsigned char *data) {
    for (node_t *curr = list->head; curr; curr = curr->next) {
        if (!memcmp(curr->data, data, curr->size)) {
            return true;
        }
    }
    return false;
}

void *list_iter_first(list_t *list) {
    if (list->head) {
        return list->head;
    } else {
        return NULL;
    }
}

void *list_iter_next(void *iter) {
    return ((node_t*)iter)->next;
}

unsigned char *list_iter_get_value(void *iter) {
    return ((node_t*)iter)->data;
}
