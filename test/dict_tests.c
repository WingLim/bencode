//
// Created by WingLim on 2020/12/21.
//

#include "dict.h"
#include "test.h"

#include <stdlib.h>
#include <string.h>

static void test_init(void **state) {
    dict_t *d;
    d = dict_init(1);
    assert_int_equal(0, d->size);
    assert_int_equal(1, d->tablesize);

    dict_free(d);
}

static void test_add(void  **state) {
    dict_t *d;
    d = dict_init(1);

    int value1 = 1;
    dict_add(d, "value1", (unsigned char*)&value1, sizeof(value1));

    int value2 = 2;
    dict_add(d, "value2", (unsigned char*)&value2, sizeof(value2));

    assert_int_equal(2, d->size);

    dict_free(d);
}

static void test_add_same_key(void **state) {
    dict_t *d;
    d = dict_init(1);

    const char *key = "hello";
    int value1 = 15;
    dict_add(d, key, (unsigned char*)&value1, sizeof(value1));
    assert_int_equal(1, d->size);

    int value2 = 12;
    dict_add(d, key, (unsigned char*)&value2, sizeof(value2));
    assert_int_equal(1, d->size);

    int got = *dict_get(d, key);
    assert_int_equal(value2, got);

    dict_free(d);
}

static void test_remove(void **state) {
    dict_t *d;
    d = dict_init(1);
    const char *key = "hello";
    int value = 15;
    dict_add(d, key, (unsigned char*)&value, sizeof(value));

    dict_remove(d, key);
    assert_int_equal(0, d->size);

    dict_free(d);
}

static void test_remove_chain_first(void **state) {
    dict_t *d;
    d = dict_init(1);
    const char *key = "hello";
    int value = 1;
    int value2 = 2;
    dict_add(d, "a", (unsigned char*)&value, sizeof(value));
    dict_add(d, "b", (unsigned char*)&value2, sizeof(value2));

    dict_remove(d, "a");
    assert_int_equal(1, d->size);

    dict_free(d);
}

static void test_remove_chain_mid(void **state) {
    dict_t *d;
    d = dict_init(1);
    const char *key = "hello";
    int value = 1;
    int value2 = 2;
    int value3 = 3;
    dict_add(d, "a", (unsigned char*)&value, sizeof(value));
    dict_add(d, "b", (unsigned char*)&value2, sizeof(value2));
    dict_add(d, "c", (unsigned char*)&value3, sizeof(value3));

    dict_remove(d, "b");
    assert_int_equal(2, d->size);

    dict_free(d);
}

static void test_foreach(void **state) {
    dict_t *d;
    d = dict_init(5);
    char *key = (char*)malloc(6);
    int value1 = 1;
    int value2 = 2;
    int value3 = 3;

    dict_add(d, "test1", (unsigned char*)&value1, sizeof(value1));
    dict_add(d, "test2", (unsigned char*)&value2, sizeof(value2));
    dict_add(d, "test3", (unsigned char*)&value3, sizeof(value3));

    const char *new_key;
    const unsigned char *val;
    FOREACH_KEY_AND_VAL(new_key, val, d) {
        if (!strcmp("test1", key)) {
            assert_int_equal(value1, *val);
        }
        if (!strcmp("test2", key)) {
            assert_int_equal(value2, *val);
        }
        if (!strcmp("test3", key)) {
            assert_int_equal(value3, *val);
        }
    }
}

int run_all_tests() {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_init),
            cmocka_unit_test(test_add),
            cmocka_unit_test(test_add_same_key),
            cmocka_unit_test(test_remove),
            cmocka_unit_test(test_remove_chain_first),
            cmocka_unit_test(test_remove_chain_mid),
            cmocka_unit_test(test_foreach),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}