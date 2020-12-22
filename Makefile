.PHONY: cmake test

BUILD_TYPE ?= Debug
BUILD_DIR ?= cmake-build-$(shell echo $(BUILD_TYPE) | tr '[:upper:]' '[:lower:]')
CODECOV ?= OFF
IWYU ?= ON

TEST_SUITES = bencode_test_int bencode_test_string bencode_test_list bencode_test_dict list_tests dict_tests

clean:
	@rm -rf $(BUILD_DIR)

cmake:
	@mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && cmake -DCODE_COVERAGE=$(CODECOV) -DIWYU=$(IWYU) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -j 4 ..

build: cmake
	@cd $(BUILD_DIR) && make bencode -j 4

test:
	@cd $(BUILD_DIR) && make $(TEST_SUITES) test CTEST_OUTPUT_ON_FAILURE=TRUE

coverage: test
	@cd $(BUILD_DIR) && make codecov CMAKE_BUILD_TYPE=$(BUILD_TYPE)