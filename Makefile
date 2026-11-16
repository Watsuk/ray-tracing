.PHONY: all configure build run test test-verbose clean help

BUILD_DIR ?= build
BUILD_TYPE ?= Debug

ifeq ($(OS),Windows_NT)
    RUN_CMD = $(BUILD_DIR)/bin/raytracer.exe
    TEST_CMD = $(BUILD_DIR)/bin/raytracer_tests.exe
else
    RUN_CMD = ./$(BUILD_DIR)/bin/raytracer
    TEST_CMD = ./$(BUILD_DIR)/bin/raytracer_tests
endif

all: build

help:
	@echo "Available targets:"
	@echo "  make configure     - Run CMake configuration (Debug)"
	@echo "  make build         - Compile library, executable, and tests"
	@echo "  make run           - Execute the Hello World raytracer application"
	@echo "  make test          - Execute unit test suite with CTest"
	@echo "  make test-verbose  - Run Catch2 tests with detailed assertion output"
	@echo "  make clean         - Remove the build directory"

configure:
	cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE)

build: configure
	cmake --build $(BUILD_DIR)

run: build
	$(RUN_CMD)

test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

test-verbose: build
	$(TEST_CMD) -s

clean:
	cmake -E rm -rf $(BUILD_DIR)
