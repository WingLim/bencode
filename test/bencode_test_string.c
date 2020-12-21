//
// Created by WingLim on 2020/12/22.
//

#include "test.h"
#include "bencode.h"

const char *endptr;

static void test_parse_string(void **state) {
    const char *raw = "5:hello";

    bencode_obj_t *b = parse_bencode(raw, &endptr);
    assert_true(b->type == BString);

    char *got = b->data.string;
    assert_string_equal("hello", got);
}

int run_all_tests() {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_parse_string),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}