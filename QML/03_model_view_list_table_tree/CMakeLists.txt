cmake_minimum_required(VERSION 3.16)
project(model_view_list_table_tree LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_add_executable(model_view_list_table_tree
    src/main.cpp
    src/ModelProvider.cpp
)

target_include_directories(model_view_list_table_tree PRIVATE src)

qt_add_qml_module(model_view_list_table_tree
    URI ModelViewShowcase
    VERSION 1.0
    QML_FILES
        qml/Main.qml
)

target_link_libraries(model_view_list_table_tree
    PRIVATE Qt6::Quick
)
