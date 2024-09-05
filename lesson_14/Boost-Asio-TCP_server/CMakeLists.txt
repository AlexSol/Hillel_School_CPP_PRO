cmake_minimum_required(VERSION 3.5)

project(Boost-Asio-TCP_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Boost-Asio-TCP_server main.cpp)

find_package(Boost REQUIRED)
if(Boost_FOUND)
    message("Boost_INCLUDE_DIRS=${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()
