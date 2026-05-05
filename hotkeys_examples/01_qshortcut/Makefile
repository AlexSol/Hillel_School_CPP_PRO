BUILD_DIR := build
TARGET := $(BUILD_DIR)/HotkeyQShortcut

.PHONY: all configure build run clean

all: build

configure:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug

build: configure
	cmake --build $(BUILD_DIR) --parallel $(shell nproc)

run: build
	$(TARGET)

clean:
	rm -rf $(BUILD_DIR)
