cmake_minimum_required(VERSION 3.16)

project(compiler_flags_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(DEMO_BROKEN "Build intentionally broken warnings example" OFF)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fno-extended-identifiers)
    add_compile_options(-fstrict-aliasing -Wall -Wextra -Werror -Wno-comment -Wdouble-promotion -Wswitch-default -Wswitch-enum -Wuninitialized -Wstrict-aliasing -Wfloat-equal -Wshadow -Wplacement-new -Wcast-align -Wconversion -Wlogical-op)
    add_compile_options(-Wduplicated-cond -Wduplicated-branches -Wrestrict -Wnull-dereference)
    add_compile_options(-ffunction-sections -fdata-sections)
    add_compile_options(-fvisibility=hidden -fvisibility-inlines-hidden)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Werror)
    add_compile_options(-Wno-comment)
    add_compile_options(-Wno-final-dtor-non-final-class)
    add_compile_options(-ffunction-sections -fdata-sections)
    add_compile_options(-fvisibility=hidden -fvisibility-inlines-hidden)
endif()

add_library(visibility_demo SHARED src/visibility_demo.cpp)
target_include_directories(visibility_demo PUBLIC include)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(visibility_demo PRIVATE -fPIC)
endif()

add_executable(flags_demo src/main.cpp)
target_link_libraries(flags_demo PRIVATE visibility_demo)

if(DEMO_BROKEN)
    add_executable(flags_warnings_bad src/warnings_bad.cpp)
endif()