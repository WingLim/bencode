//
// Created by WingLim on 2020/12/21.
//

#ifndef BENCODE_TEST_H
#define BENCODE_TEST_H

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>

int run_all_tests(void);


int main() {
    return run_all_tests();
}

#endif //BENCODE_TEST_H
