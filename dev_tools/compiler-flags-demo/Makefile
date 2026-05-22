BUILD_DIR := build
CMAKE ?= cmake
CXX := clang++

.PHONY: configure build run symbols broken clean

configure:
	$(CMAKE) -S . -B $(BUILD_DIR) -DCMAKE_CXX_COMPILER=$(CXX)

build: configure
	$(CMAKE) --build $(BUILD_DIR)

run: build
	./$(BUILD_DIR)/flags_demo

symbols: build
	nm -D --defined-only $(BUILD_DIR)/libvisibility_demo.so | c++filt

broken:
	$(CMAKE) -S . -B $(BUILD_DIR) -DCMAKE_CXX_COMPILER=$(CXX) -DDEMO_BROKEN=ON
	$(CMAKE) --build $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)