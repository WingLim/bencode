//
// Created by WingLim on 2020/12/21.
//

#include "dict.h"

#include <string.h>

static dict_entry_t *dict_entry_init(const char *key, void *value, size_t size) {
    dict_entry_t *entry = malloc(sizeof(dict_entry_t) + size);
    if (entry) {
        entry->key = malloc(strlen(key) + 1);
        if (!entry->key) {
            free(entry);
            return NULL;
        }
        memcpy(entry->key, key, strlen(key) + 1);
        entry->size = size;
        entry->next = NULL;
        memcpy(entry->value, value, size);
    }
    return entry;
}

static void dict_entry_free(dict_entry_t *entry) {
    free(entry->key);
    free(entry);
}

dict_t *dict_init(size_t tablesize) {
    dict_t *d = malloc(sizeof(dict_t));
    if (d) {
        d->size = 0;
        d->tablesize = tablesize;
        d->table = calloc(tablesize, sizeof(dict_entry_t*));
        if (!d->table) {
            free(d);
            d = NULL;
        }
    }
    return d;
}

void dict_free(dict_t *dict) {
    dict_entry_t *entry;
    dict_entry_t *next;

    for (int i = 0; i < dict->size; ++i) {
        for (entry = dict->table[i]; entry != 0; entry = next) {
            next = entry->next;

            dict_entry_free(entry);
        }
    }
    free(dict->table);
    free(dict);
}

static unsigned hashf(size_t tablesize, const char *key) {
    unsigned int seed = 131;
    unsigned int hash = 0;

    while (*key) {
        hash = hash * seed + (*key++);
    }
    return (hash & 0x7FFFFFFF) % tablesize;
}

int dict_add(dict_t *dict, const char *key, unsigned char *value, size_t size) {
    unsigned hash = hashf(dict->tablesize, key);
    dict_entry_t *entry = dict_entry_init(key, value, size);

    if (!entry) {
        return -1;
    }

    if (!dict->table[hash]) {
        dict->table[hash] = entry;
    } else {
        dict_entry_t *curr;
        curr = dict->table[hash];
        if (!strcmp(curr->key, key)) {
            dict->table[hash] = entry;
            dict->size--;
        } else {
            while (curr->next) {
                curr = curr->next;
            }
            curr->next = entry;
        }
    }
    dict->size++;
    return 0;
}

unsigned char *dict_get(dict_t *dict, const char *key) {
    unsigned hash = hashf(dict->tablesize, key);
    dict_entry_t *entry;
    for (entry = dict->table[hash];  entry; entry = entry->next) {
        if (!strcmp(entry->key, key)) {
            return entry->value;
        }
    }
    return NULL;
}

void *dict_remove(dict_t *dict, const char *key) {
    unsigned hash = hashf(dict->tablesize, key);

    dict_entry_t *prev = NULL;
    dict_entry_t *entry;

    for (entry = dict->table[hash]; entry; prev = entry, entry = entry->next) {
        if (!strcmp(entry->key, key)) {
            if (prev) {
                prev->next = entry->next;
            } else if (entry->next) {
                dict->table[hash] = entry->next;
            } else {
                dict->table[hash] = NULL;
            }
            dict_entry_free(entry);
            dict->size--;
            break;
        }
    }
}

void *dict_iter_first(dict_t *dict) {
    for (int i = 0; i < dict->tablesize; ++i) {
        dict_entry_t *entry = dict->table[i];
        if (entry) {
            return entry;
        }
    }
    return NULL;
}

void *dict_iter_next(dict_t *dict, void *iter) {
    dict_entry_t *entry = (dict_entry_t*)iter;

    if (entry->next) {
        return entry->next;
    }

    unsigned hash = hashf(dict->tablesize, entry->key);

    for (unsigned i = hash + 1; i < dict->tablesize; ++i) {
        dict_entry_t *next_entry = dict->table[i];
        if (next_entry) {
            return next_entry;
        }
    }
    return NULL;
}

const char *dict_iter_get_key(const void *iter) {
    return ((dict_entry_t*)iter)->key;
}

unsigned char *dict_iter_get_value(const void *iter) {
    return ((dict_entry_t*)iter)->value;
}