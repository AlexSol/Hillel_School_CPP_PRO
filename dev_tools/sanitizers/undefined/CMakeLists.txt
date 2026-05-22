cmake_minimum_required(VERSION 3.16)

project(undefined_sanitizer_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(undefined_sanitizer_example main.cpp)

target_compile_options(undefined_sanitizer_example PRIVATE -g -O1 -fno-omit-frame-pointer -fsanitize=undefined -fno-sanitize-recover=undefined)
target_link_options(undefined_sanitizer_example PRIVATE -fsanitize=undefined)