.PHONY: help build-all run-01 run-02 run-03 run-04 run-05 clean-all

PROJECTS := 01_minimal_qml \
            02_basic_ui_components \
            03_model_view_list_table_tree \
            04_cpp_qml_two_way \
            05_cpp_driven_architecture

help:
	@echo "Qt QML Examples — Top-level Makefile (WSL Compatible)"
	@echo ""
	@echo "Usage: make <target>"
	@echo ""
	@echo "Quick run targets (offscreen — для WSL):"
	@echo "  make run-01     — Minimal Qt Quick app"
	@echo "  make run-02     — Basic QtQuick UI Components"
	@echo "  make run-03     — ListView, TableView, TreeView"
	@echo "  make run-04     — Two-way C++ ↔ QML"
	@echo "  make run-05     — C++ Driven Architecture"
	@echo ""
	@echo "GUI targets (потребує X11 сервер або WSL 2):"
	@echo "  make run-01-gui — Запустити мінімальний приклад із графікою"
	@echo "  make run-02-gui — Запустити UI компоненти із графікою"
	@echo "  make run-03-gui — Запустити таблиці із графікою"
	@echo "  make run-04-gui — Запустити C++↔QML із графікою"
	@echo "  make run-05-gui — Запустити архітектуру із графікою"
	@echo ""
	@echo "Build/Clean targets:"
	@echo "  make build-all  — Build all projects"
	@echo "  make clean-all  — Clean all build directories"
	@echo ""
	@echo "Individual project:"
	@echo "  make PROJECT=<name> build"
	@echo "  make PROJECT=<name> run"
	@echo "  make PROJECT=<name> run-gui"
	@echo "  make PROJECT=<name> clean"
	@echo ""
	@echo "WSL Tips:"
	@echo "  • Для GUI потребується X11 сервер (VcXsrv, XLaunch тощо)"
	@echo "  • Встановіть: sudo apt install -y qt6-wayland libwayland-dev"
	@echo ""

run-01: PROJECT := 01_minimal_qml
run-01: run

run-02: PROJECT := 02_basic_ui_components
run-02: run

run-03: PROJECT := 03_model_view_list_table_tree
run-03: run

run-04: PROJECT := 04_cpp_qml_two_way
run-04: run

run-05: PROJECT := 05_cpp_driven_architecture
run-05: run

run-01-gui: PROJECT := 01_minimal_qml
run-01-gui: run-gui

run-02-gui: PROJECT := 02_basic_ui_components
run-02-gui: run-gui

run-03-gui: PROJECT := 03_model_view_list_table_tree
run-03-gui: run-gui

run-04-gui: PROJECT := 04_cpp_qml_two_way
run-04-gui: run-gui

run-05-gui: PROJECT := 05_cpp_driven_architecture
run-05-gui: run-gui

run:
	@if [ -z "$(PROJECT)" ]; then \
		echo "Error: PROJECT not set"; \
		echo "Usage: make PROJECT=<name> run"; \
		exit 1; \
	fi
	@$(MAKE) -C $(PROJECT) run

run-gui:
	@if [ -z "$(PROJECT)" ]; then \
		echo "Error: PROJECT not set"; \
		echo "Usage: make PROJECT=<name> run-gui"; \
		exit 1; \
	fi
	@$(MAKE) -C $(PROJECT) run-gui

build:
	@if [ -z "$(PROJECT)" ]; then \
		echo "Error: PROJECT not set"; \
		echo "Usage: make PROJECT=<name> build"; \
		exit 1; \
	fi
	@$(MAKE) -C $(PROJECT) build

clean:
	@if [ -z "$(PROJECT)" ]; then \
		echo "Error: PROJECT not set"; \
		echo "Usage: make PROJECT=<name> clean"; \
		exit 1; \
	fi
	@$(MAKE) -C $(PROJECT) clean

build-all:
	@for proj in $(PROJECTS); do \
		echo "Building $$proj..."; \
		$(MAKE) -C $$proj build || exit 1; \
	done
	@echo "All projects built successfully"

clean-all:
	@for proj in $(PROJECTS); do \
		echo "Cleaning $$proj..."; \
		$(MAKE) -C $$proj clean; \
	done
	@echo "All projects cleaned"
