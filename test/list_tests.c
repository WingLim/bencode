//
// Created by WingLim on 2020/12/21.
//

#include "list.h"
#include "test.h"

#include <stdbool.h>

static void test_init(void **state) {
    list_t *l = list_init();

    assert_int_equal(0, l->size);
    assert_null(l->head);

    list_free(l);
}

static void test_add(void **state) {
    list_t *l = list_init();

    int want = 100;
    list_add(l, (unsigned char*)&want, sizeof(want));

    bool status = list_contains(l, (unsigned char*)&want);
    assert_true(status);

    list_free(l);
}

static void test_remove(void **state) {
    list_t *l = list_init();

    int want = 100;
    list_add(l, (unsigned char*)&want, sizeof(want));

    list_remove(l, (unsigned char*)&want);

    bool status = list_contains(l, (unsigned char*)&want);
    assert_false(status);
    assert_int_equal(0, l->size);

    list_free(l);
}

int run_all_tests() {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_init),
            cmocka_unit_test(test_add),
            cmocka_unit_test(test_remove),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}