//
// Created by WingLim on 2020/12/21.
//

//
// Created by lewy on 2020/12/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "bencode.h"

static bencode_obj_t *new_bencode_obj(void) {
    bencode_obj_t *b = malloc(sizeof(bencode_obj_t));
    memset(b->sha1, 0, SHA1_BLOCK_SIZE);
    return b;
}

void bencode_obj_free(bencode_obj_t *b) {
    switch (b->type) {
        case BInt:
            free(b);
            break;
        case BString:
            free(b->data.string);
            free(b);
            break;
        case BList: {
            const unsigned char *node;

            FOREACH_NODE(node, b->data.list) {
                bencode_obj_free(*((bencode_obj_t**)node));
            }

            list_free(b->data.list);
            free(b);
            break;
        }
        case BDict: {
            const char *key;
            const unsigned char *value;

            FOREACH_KEY_AND_VAL(key, value, b->data.dictionary) {
                bencode_obj_free(*((bencode_obj_t**)value));
            }

            dict_free(b->data.dictionary);
            free(b);
            break;
        }
    }
}

static bencode_obj_t *parse_int(const char *benc, const char **endptr) {
    long val;
    bencode_obj_t *b;
    *endptr = benc;

    assert(*benc == 'i');
    benc++;

    val = strtol(benc, (char**)endptr, 10);
    assert(**endptr == 'e');
    (*endptr)++;

    b = new_bencode_obj();
    assert(b);

    b->type = BInt;
    b->data.integer = val;

    return b;
}

static bencode_obj_t *parse_string(const char *benc, const char **endptr) {
    long len = 0;
    bencode_obj_t *b;
    *endptr = benc;

    len = strtol(benc, (char**)endptr, 10);
    assert(**endptr == ':');
    (*endptr)++;

    char *s = malloc(sizeof(char)*(len + 1));
    memcpy(s, *endptr, len);
    s[len] = '\0';
    (*endptr) += len;

    b = new_bencode_obj();
    assert(b);

    b->type = BString;
    b->data.string = s;

    return b;
}

static bencode_obj_t *parse_list(const char *benc, const char **endptr) {
    bencode_obj_t *b;

    assert(*benc == 'l');
    *endptr = benc + 1;

    b = new_bencode_obj();
    assert(b);

    b->type = BList;
    b->data.list = list_init();

    while (**endptr != 'e') {
        benc = *endptr;
        bencode_obj_t *elem = parse_bencode(benc, endptr);
        assert(elem);

        list_add(b->data.list, (unsigned char*)&elem, sizeof(elem));
    }

    assert(**endptr == 'e');
    (*endptr)++;

    return b;
}

static bencode_obj_t *parse_dict(const char *benc, const char **endptr) {
    bencode_obj_t *b;

    assert(*benc == 'd');
    *endptr = benc + 1;

    b = new_bencode_obj();
    b->type = BDict;

    b->data.dictionary = dict_init(1);
    assert(b->data.dictionary);

    while (**endptr != 'e') {
        benc = *endptr;
        bencode_obj_t *key = parse_string(benc, endptr);
        assert(key);
        assert(*endptr > benc);

        benc = *endptr;
        bencode_obj_t *value = parse_bencode(benc, endptr);
        assert(value);
        assert(*endptr > benc);

        if (!strcmp(key->data.string, "info")) {
            assert(benc[0] == 'd');
            assert((*endptr)[-1] == 'e');
            sha1_compute(benc, *endptr - benc, value->sha1);
        }

        dict_add(b->data.dictionary, (char*)key->data.string,
                 (unsigned char*)&value, sizeof(value));

        bencode_obj_free(key);
    }

    assert(**endptr == 'e');
    (*endptr)++;

    return b;
}

bencode_obj_t *parse_bencode(const char *benc, const char **endptr) {
    char c = benc[0];
    switch (c) {
        case 'd': return parse_dict(benc, endptr);
        case 'l': return parse_list(benc, endptr);
        case 'i': return parse_int(benc, endptr);
        default: return parse_string(benc, endptr);
    }
}

void print_indent(int indent) {
    for (int i = 0; i < indent; ++i) {
        printf(" ");
    }
}

bencode_obj_t *transfer_to_bencode_obj(unsigned char value[]) {
    return *((bencode_obj_t**) value);
}

void print_bencode(bencode_obj_t *b, int indent) {
    print_indent(indent);
    switch (b->type) {
        case BInt:
            printf("Int: %lld\n", b->data.integer);
            break;
        case BString:
            printf("String: %s\n", b->data.string);
            break;
        case BList: {
            printf("List: [\n");
            list_t *l = b->data.list;
            const unsigned char *node;

            FOREACH_NODE(node, b->data.list) {
                print_bencode(*((bencode_obj_t**)node), indent + 2);
            }
            print_indent(indent);
            printf("]\n");
            break;
        }
        case BDict: {
            const char *key;
            const unsigned char *value;

            printf("Dict: {\n");
            FOREACH_KEY_AND_VAL(key, value, b->data.dictionary) {
                print_indent(indent + 2);
                printf("Key: %s\n", key);
                print_bencode(*((bencode_obj_t**)value), indent + 2);
            }
            print_indent(indent);
            printf("}\n");
            break;
        }
    }
}
