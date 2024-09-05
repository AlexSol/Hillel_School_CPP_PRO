cmake_minimum_required(VERSION 3.10)

project(httpClient-boost-Beast-vcpkg)

find_package(boost_beast REQUIRED CONFIG)

add_executable(httpClient-boost-Beast-vcpkg main.cpp)

target_link_libraries(httpClient-boost-Beast-vcpkg PRIVATE Boost::beast)