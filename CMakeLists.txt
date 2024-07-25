cmake_minimum_required(VERSION 3.5)

# Project Name Version & main Languages.
project(hillelSchoolCppPro VERSION 1.0.0 LANGUAGES CXX)

# //Костиль. Потрібно вказати шлях до компілятора. 
# Це можна зробити через set або через змінну середовища 
# або через змінну середовища в самому cmake

# через set
# set(CMAKE_C_COMPILER /usr/bin/clang-18)
# set(CMAKE_CXX_COMPILER /usr/bin/clang++-18)

# через змінну середовища
set(ENV{CC} /usr/bin/clang-18)
set(ENV{CXX} /usr/bin/clang++-18)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
endif()


set(CMAKE_CXX_STANDARD 23)

add_subdirectory(lesson_1)
add_subdirectory(lesson_2)
add_subdirectory(lesson_3)
add_subdirectory(lesson_4)
add_subdirectory(lesson_5)
