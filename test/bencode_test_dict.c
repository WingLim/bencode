//
// Created by WingLim on 2020/12/22.
//

#include "test.h"
#include "bencode.h"

#include <string.h>

const char *endptr;

static void test_dict_val_int(void **state) {
    const char *raw = "d5:helloi10ee";

    bencode_obj_t *b = parse_bencode(raw, &endptr);
    assert_true(b->type == BDict);

    dict_t *d = b->data.dictionary;
    bencode_obj_t *b2 = transfer_to_bencode_obj(dict_get(d, "hello"));
    assert_true(b2->type == BInt);

    long got = b2->data.integer;
    assert_int_equal(10, got);
}

static void test_dict_val_string(void **state) {
    const char *raw = "d5:hello5:worlde";

    bencode_obj_t *b = parse_bencode(raw, &endptr);
    assert_true(b->type == BDict);

    dict_t *d = b->data.dictionary;
    bencode_obj_t *b2 = transfer_to_bencode_obj(dict_get(d, "hello"));
    assert_true(b2->type == BString);

    char *got = b2->data.string;
    assert_string_equal("world", got);
}

static void test_dict_val_list(void **state) {
    const char *raw = "d5:helloli10eee";

    bencode_obj_t *b = parse_bencode(raw, &endptr);
    assert_true(b->type == BDict);

    dict_t *d = b->data.dictionary;
    bencode_obj_t *b2 = transfer_to_bencode_obj(dict_get(d, "hello"));
    assert_true(b2->type == BList);
}

static void test_dict_val_dict(void **state) {
    const char *raw = "d5:hellod5:worldi10eee";

    bencode_obj_t *b = parse_bencode(raw, &endptr);
    assert_true(b->type == BDict);

    dict_t *d = b->data.dictionary;
    bencode_obj_t *b2 = transfer_to_bencode_obj(dict_get(d, "hello"));
    assert_true(b2->type == BDict);
}

static void test_dict_info(void **state) {
    const char *raw = "d4:infod5:helloi4eee";
    unsigned char want[20] = {0xf7,0xc5,0x55,0xf8,0xa4,0x71,0x4a,0x13,0xc7,0xb2,0xf4,0x3d,0x25,0xcb,0xcd,0xd2,0x93,0x51,0x2a,0xf9};

    bencode_obj_t *b = parse_bencode(raw, &endptr);
    assert_true(b->type == BDict);

    dict_t *d = b->data.dictionary;
    bencode_obj_t *b2 = transfer_to_bencode_obj(dict_get(d, "info"));
    assert_true( memcmp(want, b2->sha1, 20) == 0 );
}

int run_all_tests() {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_dict_val_int),
            cmocka_unit_test(test_dict_val_string),
            cmocka_unit_test(test_dict_val_list),
            cmocka_unit_test(test_dict_val_dict),
            cmocka_unit_test(test_dict_info),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}