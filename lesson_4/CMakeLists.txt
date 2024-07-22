cmake_minimum_required(VERSION 3.5)

# Project Name Version & main Languages.
project(lesson_3 VERSION 1.0.0 LANGUAGES CXX)


add_executable(thread thread.cpp)
add_executable(thread_value thread_value.cpp)

add_executable(sleep_for sleep_for.cpp)
add_executable(sleep_until sleep_until.cpp)

add_executable(race_condition  race_condition.cpp)
# add_executable(deadlock  deadlock.cpp)

add_executable(atomic  atomic.cpp)

add_executable(shared_mutex  shared_mutex.cpp)
add_executable(scoped_lock   scoped_lock.cpp)

add_executable(condition_variable  condition_variable.cpp)