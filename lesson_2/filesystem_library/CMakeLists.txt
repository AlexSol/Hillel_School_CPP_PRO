cmake_minimum_required(VERSION 3.5)

project(filesystem_examples VERSION 1.0.0 LANGUAGES CXX)

# //Костиль. Потрібно вказати шлях до компілятора. 
# Це можна зробити через set або через змінну середовища 
# або через змінну середовища в самому cmake

# через set
# set(CMAKE_C_COMPILER /usr/bin/clang-18)
# set(CMAKE_CXX_COMPILER /usr/bin/clang++-18)

# через змінну середовища
set(ENV{CC} /usr/bin/clang-18)
set(ENV{CXX} /usr/bin/clang++-18)

set(CMAKE_CXX_STANDARD 23)

add_executable(example_1 example_1.cpp)

# Копіювання файлу через потоки
add_executable(copy_file_use_iostream example_2.cpp)

# Копіювання файлу через std::filesystem
add_executable(copy_file_use_filesystem example_3.cpp)

# Створення файлу std::filesystem
add_executable(create_file_filesystem example_4.cpp)
