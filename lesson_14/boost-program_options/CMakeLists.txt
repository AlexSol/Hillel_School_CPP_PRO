cmake_minimum_required(VERSION 3.5)

project(boost_program_options_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS program_options REQUIRED)
if(Boost_FOUND)
    message("Boost_INCLUDE_DIRS=${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable(boost_program_options_example main.cpp)

target_link_libraries(boost_program_options_example Boost::program_options)
