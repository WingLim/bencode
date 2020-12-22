//
// Created by WingLim on 2020/12/22.
//

#include "test.h"
#include "sha1.h"

#include <string.h>

void assert_sha1(const char *string, char want[41]) {
    BYTE buf[SHA1_BLOCK_SIZE];
    char got[41];
    sha1_compute(string, strlen(string), buf);
    sha1_format(buf, got);
    assert_true(strncmp(got, want, 40) == 0);
}

static void test_sha1_1(void **state) {
    const char *string = "abc";
    char want[] = "a9993e364706816aba3e25717850c26c9cd0d89d";

    assert_sha1(string, want);
}

static void test_sha1_2(void **state) {
    const char *string = "";
    char want[] = "da39a3ee5e6b4b0d3255bfef95601890afd80709";

    assert_sha1(string, want);
}

static void test_sha1_3(void **state) {
    const char *string = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    char want[] = "84983e441c3bd26ebaae4aa1f95129e5e54670f1";

    assert_sha1(string, want);
}

static void test_sha1_4(void **state) {
    const char *string = "aaaaaaaaaa";
    char want[] = "3495ff69d34671d1e15b33a63c1379fdedd3a32a";

    assert_sha1(string, want);
}

int run_all_tests() {
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_sha1_1),
            cmocka_unit_test(test_sha1_2),
            cmocka_unit_test(test_sha1_3),
            cmocka_unit_test(test_sha1_4),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}