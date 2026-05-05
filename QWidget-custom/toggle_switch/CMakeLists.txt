cmake_minimum_required(VERSION 3.5)

project(ToggleSwitchDemo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ToggleSwitchDemo
        MANUAL_FINALIZATION
        toggle_switch.cpp
    )
else()
    add_executable(ToggleSwitchDemo toggle_switch.cpp)
endif()

target_link_libraries(ToggleSwitchDemo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(ToggleSwitchDemo PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_finalize_executable(ToggleSwitchDemo)
endif()
