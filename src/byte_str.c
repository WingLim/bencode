//
// Created by WingLim on 2021/1/5.
//

#include "byte_str.h"

#include <stdlib.h>
#include <string.h>

byte_str_t *byte_str_new(size_t size, const unsigned char *raw) {
    byte_str_t *s;
    s = malloc(sizeof(byte_str_t) + size + 1);
    if (s) {
        memcpy(s->str, raw, size);
        s->str[size] = '\0';
        s->size = size;
    }
    return s;
}
void byte_str_free(byte_str_t *string) {
    free(string);
}