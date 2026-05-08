cmake_minimum_required(VERSION 3.5)

project(QTableWidget_perf VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QTableWidget_perf
        MANUAL_FINALIZATION
        main.cpp
    )
else()
    add_executable(QTableWidget_perf main.cpp)
endif()

target_link_libraries(QTableWidget_perf PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(QTableWidget_perf PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_finalize_executable(QTableWidget_perf)
endif()
