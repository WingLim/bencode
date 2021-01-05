//
// Created by WingLim on 2020/12/21.
//

#ifndef BENCODE_BENCODE_H
#define BENCODE_BENCODE_H

#include "dict.h"
#include "list.h"
#include "sha1.h"

typedef enum {
    BString,
    BInt,
    BList,
    BDict
} btype_t;

typedef struct bencode_obj {
    btype_t type;
    union {
        int64_t integer;
        unsigned char *string;
        list_t *list;
        dict_t *dictionary;
    } data;
    unsigned char sha1[SHA1_BLOCK_SIZE];
} bencode_obj_t;

bencode_obj_t   *parse_bencode(const char *benc, const char **endptr);
void            bencode_obj_free(bencode_obj_t *b);
bencode_obj_t   *transfer_to_bencode_obj(unsigned char value[]);
void            print_bencode(bencode_obj_t *b, int indent);

#endif //BENCODE_BENCODE_H
