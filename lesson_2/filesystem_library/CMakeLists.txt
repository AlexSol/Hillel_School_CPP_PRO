cmake_minimum_required(VERSION 3.5)

project(filesystem_examples VERSION 1.0.0 LANGUAGES CXX)

# виведення списку файлів і пакок у директорії
add_executable(print_files_dirs
    print_files_dirs.cpp)

# Копіювання файлу через потоки
add_executable(copy_file_use_iostream
    copy_file_use_iostream.cpp)

# Копіювання файлу через std::filesystem
add_executable(copy_file_use_filesystem
    copy_file_use_filesystem.cpp)

# Створення файлу std::filesystem
# add_executable(create_file_filesystem example_4.cpp)

# Видалення файлу std::filesystem
add_executable(remove_file_filesystem
    remove_file_filesystem.cpp)

# створення папки std::filesystem
add_executable(create_dir_filesystem
    create_dir_filesystem.cpp)

# Реверсивне видалення папки std::filesystem
add_executable(remove_dir_filesystem
    remove_dir_filesystem.cpp)

# Реверсивне копіювання папки std::filesystem
add_executable(copy_directory
    copy_directory.cpp)

# std::filesystem - дозволи
add_executable(permissions
    permissions.cpp)

# std::filesystem - дозволи
add_executable(permissions_1
    permissions_1.cpp)
