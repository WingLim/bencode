//
// Created by WingLim on 2020/12/21.
//

#ifndef C_DATA_STRUCTURES_DICT_H
#define C_DATA_STRUCTURES_DICT_H

#include <stdlib.h>

typedef struct dict_entry {
    struct dict_entry *next;
    char *key;
    size_t size;
    unsigned char value[];
} dict_entry_t;

typedef struct dict {
    unsigned size;
    unsigned tablesize;
    struct dict_entry **table;
} dict_t;

dict_t          *dict_init(size_t tablesize);
void            dict_free(dict_t *dict);
int             dict_add(dict_t *dict, const char *key, unsigned char *value, size_t size);
unsigned char   *dict_get(dict_t *dict, const char *key);
void            *dict_remove(dict_t *dict, const char *key);

void            *dict_iter_first(dict_t *dict);
void            *dict_iter_next(dict_t *dict, void *iter);
const char      *dict_iter_get_key(const void *iter);
unsigned char   *dict_iter_get_value(const void *iter);

#define FOREACH_KEY_AND_VAL(_key, _val, _dict_ptr) \
    for(void *_iter = dict_iter_first(_dict_ptr); \
        _iter \
        && (_key = dict_iter_get_key(_iter)) \
        && (_val = dict_iter_get_value(_iter)); \
        _iter = dict_iter_next(_dict_ptr, _iter))

#endif //C_DATA_STRUCTURES_DICT_H
