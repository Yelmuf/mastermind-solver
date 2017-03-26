cmake_minimum_required(VERSION 2.8)
project(mastermind_solver)

set(CMAKE_CXX_STANDARD c99)

set(SOURCE_FILES main.c)
add_executable(mastermind_solver ${SOURCE_FILES})
