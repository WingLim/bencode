//
// Created by WingLim on 2021/1/5.
//

#ifndef BENCODE_BYTE_STR_H
#define BENCODE_BYTE_STR_H

#include <stddef.h>

typedef struct byte_str {
    size_t size;
    unsigned char str[];
} byte_str_t;

byte_str_t  *byte_str_new(size_t size, const unsigned char *raw);
void        byte_str_free(byte_str_t *string);

#endif //BENCODE_BYTE_STR_H
