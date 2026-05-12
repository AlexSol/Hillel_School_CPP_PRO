cmake_minimum_required(VERSION 3.16)
project(cpp_qml_two_way LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_add_executable(cpp_qml_two_way
    src/main.cpp
    src/BridgeBackend.cpp
)

target_include_directories(cpp_qml_two_way PRIVATE src)

qt_add_qml_module(cpp_qml_two_way
    URI CppQmlTwoWay
    VERSION 1.0
    QML_FILES
        qml/Main.qml
)

target_link_libraries(cpp_qml_two_way
    PRIVATE Qt6::Quick
)
