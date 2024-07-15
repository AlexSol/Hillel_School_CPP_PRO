cmake_minimum_required(VERSION 3.5)

# Project Name Version & main Languages.
project(lesson_3 VERSION 1.0.0 LANGUAGES CXX)


add_subdirectory(Containers_library)

add_executable(unique_ptr unique_ptr.cpp)
add_executable(nullptr  nullptr.cpp)
add_executable(shared_ptr  shared_ptr.cpp)
add_executable(weak_ptr  weak_ptr.cpp)