include(CMocka)

include_directories(${CMOCKA_INCLUDE_DIR})

function(add_test_suite _testName)
    add_executable(${_testName} ${_testName}.c)
    target_link_libraries(${_testName} bencode cmocka)
    add_test(${_testName} ${CMAKE_CURRENT_BINARY_DIR}/${_testName})
endfunction()

add_test_suite(bencode_test_int)
add_test_suite(bencode_test_string)
add_test_suite(bencode_test_list)
add_test_suite(bencode_test_dict)
add_test_suite(list_tests)
add_test_suite(dict_tests)
add_test_suite(sha1_tests)