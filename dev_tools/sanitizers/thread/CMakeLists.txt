cmake_minimum_required(VERSION 3.16)

project(thread_sanitizer_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)

add_executable(thread_sanitizer_example main.cpp)
target_link_libraries(thread_sanitizer_example PRIVATE Threads::Threads)

target_compile_options(thread_sanitizer_example PRIVATE -g -O1 -fno-omit-frame-pointer -fsanitize=thread)
target_link_options(thread_sanitizer_example PRIVATE -fsanitize=thread)