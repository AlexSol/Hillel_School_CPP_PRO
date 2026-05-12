cmake_minimum_required(VERSION 3.16)
project(basic_ui_components LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_add_executable(basic_ui_components
    main.cpp
)

qt_add_qml_module(basic_ui_components
    URI BasicUiComponents
    VERSION 1.0
    QML_FILES
        qml/Main.qml
)

target_link_libraries(basic_ui_components
    PRIVATE Qt6::Quick
)
