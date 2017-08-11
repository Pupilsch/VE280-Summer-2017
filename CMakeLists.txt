cmake_minimum_required(VERSION 3.7)
project(calc)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES calc.cpp dlist.cpp)
add_executable(calc ${SOURCE_FILES})
