cmake_minimum_required(VERSION 3.16)
project(cpp_driven_architecture LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_add_executable(cpp_driven_architecture
    src/main.cpp
    src/TaskModel.cpp
    src/AppController.cpp
)

target_include_directories(cpp_driven_architecture PRIVATE src)

qt_add_qml_module(cpp_driven_architecture
    URI CppDrivenArchitecture
    VERSION 1.0
    QML_FILES
        qml/Main.qml
)

target_link_libraries(cpp_driven_architecture
    PRIVATE Qt6::Quick
)
