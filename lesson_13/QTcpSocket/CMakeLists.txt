cmake_minimum_required(VERSION 3.14)

project(QTcpSocket LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core  Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core  Network)

add_executable(QTcpSocket
  main.cpp
)
target_link_libraries(QTcpSocket
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network)
