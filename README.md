# Bencode

A bencode parser implement by C.

![build](https://github.com/WingLim/bencode/workflows/build/badge.svg)
[![codecov](https://codecov.io/gh/WingLim/bencode/branch/main/graph/badge.svg?token=JKZFSM65UD)](https://codecov.io/gh/WingLim/bencode)

## Usage

### With CMake

`bencode.cmake`:

```cmake
include(ExternalProject)
ExternalProject_Add(bencode_ep
        URL https://github.com/WingLim/bencode/archive/v1.0.0.tar.gz

        CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}
        -DBUILD_STATIC_LIB=ON
        -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=Debug
        -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=Release
        -DUNIT_TEST=OFF

        BUILD_COMMAND $(MAKE) bencode
        INSTALL_COMMAND "")

add_library(bencode STATIC IMPORTED GLOBAL)
ExternalProject_Get_Property(bencode_ep binary_dir)

set_property(TARGET bencode PROPERTY IMPORTED_LOCATION "${binary_dir}/src/libbencode.a")
set_property(TARGET bencode PROPERTY IMPORTED_LOCATION_DEBUG "${binary_dir}/src/Debug/libbencode.a")
set_property(TARGET bencode PROPERTY IMPORTED_LOCATION_RELEASE "${binary_dir}/src/Release/libbencode.a")

add_dependencies(bencode bencode_ep)

ExternalProject_Get_Property(bencode_ep source_dir)
set(BENCODE_INCLUDE_DIR ${source_dir}/include GLOBAL)
```

Add below include in your `CMakeLists.txt`:

```cmake
include(bencode.cmake)
```
