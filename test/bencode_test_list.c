//
// Created by WingLim on 2020/12/22.
//

#include "test.h"
#include "bencode.h"

const char *endptr;

static int teardown(void  **state) {
    bencode_obj_free(*state);
    return 0;
}

static void test_list_int(void **state) {
    const char *raw = "li10ee";

    bencode_obj_t *b = parse_bencode(raw, &endptr);
    assert_true(b->type == BList);

    list_t *l = b->data.list;
    bencode_obj_t *b2 = transfer_to_bencode_obj(l->head->data);
    assert_true(b2->type == BInt);

    long got = b2->data.integer;
    assert_int_equal(10, got);

    *state = b;
}

static void test_list_string(void **state) {
    const char *raw = "l5:helloe";

    bencode_obj_t *b = parse_bencode(raw, &endptr);
    assert_true(b->type == BList);

    list_t *l = b->data.list;
    bencode_obj_t *b2 = transfer_to_bencode_obj(l->head->data);
    assert_true(b2->type == BString);

    char *got = b2->data.string;
    assert_string_equal("hello", got);

    *state = b;
}

static void test_list_list(void **state) {
    const char *raw = "lli10eee";

    bencode_obj_t *b = parse_bencode(raw, &endptr);
    assert_true(b->type == BList);

    list_t *l = b->data.list;
    bencode_obj_t *b2 = transfer_to_bencode_obj(l->head->data);
    assert_true(b2->type == BList);

    list_t *l2 = b2->data.list;
    bencode_obj_t *b3 = transfer_to_bencode_obj(l2->head->data);
    int got = b3->data.integer;
    assert_int_equal(10, got);

    *state = b;
}

static void test_list_dict(void **state) {
    const char *raw = "ld5:hello5:worldee";

    bencode_obj_t *b = parse_bencode(raw, &endptr);
    assert_true(b->type == BList);

    list_t *l = b->data.list;
    bencode_obj_t *b2 = transfer_to_bencode_obj(l->head->data);
    assert_true(b2->type == BDict);

    dict_t *d = b2->data.dictionary;
    bencode_obj_t *b3 = transfer_to_bencode_obj(dict_get(d, "hello"));
    char *got = b3->data.string;
    assert_string_equal("world", got);
    print_bencode(b, 0);

    *state = b;
}


int run_all_tests() {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test_teardown(test_list_int, teardown),
            cmocka_unit_test_teardown(test_list_string, teardown),
            cmocka_unit_test_teardown(test_list_list, teardown),
            cmocka_unit_test_teardown(test_list_dict, teardown),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}