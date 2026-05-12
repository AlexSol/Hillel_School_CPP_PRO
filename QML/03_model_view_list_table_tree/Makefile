BUILD_DIR ?= build
APP ?= model_view_list_table_tree
QT_PLATFORM ?= offscreen

.PHONY: configure build run run-gui clean

configure:
	cmake -S . -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=Debug

build: configure
	cmake --build $(BUILD_DIR) -j

run: build
	QT_QPA_PLATFORM=$(QT_PLATFORM) QT_LOGGING_RULES="qt.qpa.*=false" ./$(BUILD_DIR)/$(APP)

run-gui: build
	QT_QPA_PLATFORM=xcb ./$(BUILD_DIR)/$(APP) 2>/dev/null || QT_QPA_PLATFORM=offscreen ./$(BUILD_DIR)/$(APP)

clean:
	rm -rf $(BUILD_DIR)
