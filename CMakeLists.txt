cmake_minimum_required(VERSION 3.17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(bencode)

option(IWYU "Run include-what-you-use with the compiler" OFF)
if (IWYU)
    find_program(IWYU_COMMAND NAMES include-what-you-use iwyu)
    if (NOT IWYU_COMMAND)
        message(FATAL_ERROR "CMAKE_IWYU is ON but include-what-you-use is not found!")
    endif ()
    set(CMAKE_C_INCLUDE_WHAT_YOU_USE "${IWYU_COMMAND};-Xiwyu")
endif ()

enable_testing()

add_library(bencode
        src/bencode.c
        src/list.c
        src/dict.c
        src/sha1.c)

target_include_directories(bencode
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(test)