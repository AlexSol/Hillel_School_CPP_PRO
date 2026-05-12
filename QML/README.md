# Qt QML Examples

This folder contains standalone Qt 6 QML demo projects.

## Projects

- `01_minimal_qml` - minimal Qt Quick app.
- `02_basic_ui_components` - base QtQuick Controls UI components.
- `03_model_view_list_table_tree` - ListView, TableView, TreeView with C++ models.
- `04_cpp_qml_two_way` - two-way bridge: QML calls C++, C++ calls QML.
- `05_cpp_driven_architecture` - C++-driven architecture where QML mainly renders UI.

## Quick Build

Each subproject has its own `Makefile`.

Example:

```bash
cd 04_cpp_qml_two_way
make run
```

Common targets:

- `make configure`
- `make build`
- `make run` — запуск у headless режимі (WSL-friendly)
- `make run-gui` — запуск з GUI (потребує X11)
- `make clean`

## WSL Support

Всі приклади переведені на WSL-сумісний режим.

### Встановлення залежностей для WSL

```bash
sudo apt update
sudo apt install -y qt6-declarative-dev qt6-base-dev \
  qml6-module-qtquick qml6-module-qtquick-controls \
  qml6-module-qtquick-layouts \
  libqt6gui6 libqt6qml6 qt6-wayland
```

### Запуск у WSL

**Без GUI (headless):**
```bash
cd 01_minimal_qml
make run
```

**З GUI (потребує X11 сервер):**

1. Встановіть на Windows X11 сервер:
   - [VcXsrv](https://sourceforge.net/projects/vcxsrv/) — найпростіший
   - [Xming](http://www.straightrunning.com/XmingNotes/)
   - WSL 2 з Windows 11 має вбудований підтримку GUI

2. Запустіть додаток:
```bash
cd 01_minimal_qml
make run-gui
```

Або вручну:
```bash
export DISPLAY=:0
cd 01_minimal_qml
./build/minimal_qml
```

