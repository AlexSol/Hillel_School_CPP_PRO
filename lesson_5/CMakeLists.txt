cmake_minimum_required(VERSION 3.5)

# Project Name Version & main Languages.
project(lesson_5 VERSION 1.0.0 LANGUAGES CXX)

add_executable(call_once call_once.cpp)
add_executable(call_once-exemple-2 call_once-exemple-2.cpp)

add_executable(async async.cpp)
add_executable(async-exemple-2 async-exemple-2.cpp)
add_executable(async-exemple-3 async-exemple-3.cpp)

add_executable(packaged_task packaged_task.cpp)
add_executable(packaged_task-exception packaged_task-exception.cpp)

add_executable(shared_future shared_future.cpp)

add_executable(promise promise.cpp)

add_executable(lambda lambda.cpp)
add_executable(lambda_trable lambda_trable.cpp)


