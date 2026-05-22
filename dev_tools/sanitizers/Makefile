BUILD_DIR := build
CMAKE ?= cmake
CXX := clang++

.PHONY: all address leak undefined thread run-address run-leak run-undefined run-thread clean list

all: address leak undefined thread

list:
	@printf '%s\n' address leak undefined thread

address:
	$(CMAKE) -S address -B $(BUILD_DIR)/address -DCMAKE_CXX_COMPILER=$(CXX)
	$(CMAKE) --build $(BUILD_DIR)/address

leak:
	$(CMAKE) -S leak -B $(BUILD_DIR)/leak -DCMAKE_CXX_COMPILER=$(CXX)
	$(CMAKE) --build $(BUILD_DIR)/leak

undefined:
	$(CMAKE) -S undefined -B $(BUILD_DIR)/undefined -DCMAKE_CXX_COMPILER=$(CXX)
	$(CMAKE) --build $(BUILD_DIR)/undefined

thread:
	$(CMAKE) -S thread -B $(BUILD_DIR)/thread -DCMAKE_CXX_COMPILER=$(CXX)
	$(CMAKE) --build $(BUILD_DIR)/thread

run-address: address
	./$(BUILD_DIR)/address/address_sanitizer_example

run-leak: leak
	./$(BUILD_DIR)/leak/leak_sanitizer_example

run-undefined: undefined
	./$(BUILD_DIR)/undefined/undefined_sanitizer_example

run-thread: thread
	./$(BUILD_DIR)/thread/thread_sanitizer_example

clean:
	rm -rf $(BUILD_DIR)