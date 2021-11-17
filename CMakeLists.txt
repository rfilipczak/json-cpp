cmake_minimum_required(VERSION 3.20)
project(json)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(
        -std=c++2a
        -Wpedantic
        -Wall
        -Wextra
        -Wconversion
)

add_executable(example example.cpp)
