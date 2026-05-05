cmake_minimum_required(VERSION 3.5)

project(QSS_Demo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Ресурси: упаковуємо QSS-файли в бінарник
qt_add_resources(QSS_RESOURCES resources.qrc)

set(PROJECT_SOURCES
    main.cpp
    ${QSS_RESOURCES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QSS_Demo
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(QSS_Demo ${PROJECT_SOURCES})
endif()

target_link_libraries(QSS_Demo PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(QSS_Demo PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_finalize_executable(QSS_Demo)
endif()
