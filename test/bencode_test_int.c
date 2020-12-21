//
// Created by WingLim on 2020/12/22.
//

#include "test.h"
#include "bencode.h"

const char *endptr;

static void test_parse_int(void **state) {
    const char *raw = "i10e";

    bencode_obj_t *b = parse_bencode(raw, &endptr);
    assert_true(b->type = BInt);

    long got = b->data.integer;
    assert_int_equal(10, got);
}

int run_all_tests() {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_parse_int),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}