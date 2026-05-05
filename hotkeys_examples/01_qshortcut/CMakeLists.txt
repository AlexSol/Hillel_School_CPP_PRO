cmake_minimum_required(VERSION 3.5)
project(HotkeyQShortcut VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(HotkeyQShortcut main.cpp)
target_link_libraries(HotkeyQShortcut PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
