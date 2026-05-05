cmake_minimum_required(VERSION 3.5)
project(HotkeyQHotkey VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(HotkeyQHotkey main.cpp)
target_link_libraries(HotkeyQHotkey PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

find_package(QHotkey QUIET)
if(TARGET QHotkey::QHotkey)
    target_link_libraries(HotkeyQHotkey PRIVATE QHotkey::QHotkey)
    target_compile_definitions(HotkeyQHotkey PRIVATE HAVE_QHOTKEY)
elseif(TARGET QHotkey)
    target_link_libraries(HotkeyQHotkey PRIVATE QHotkey)
    target_compile_definitions(HotkeyQHotkey PRIVATE HAVE_QHOTKEY)
endif()
