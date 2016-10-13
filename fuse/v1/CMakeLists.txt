cmake_minimum_required(VERSION 3.6)
project(v1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES hello.c)
add_executable(v1 ${SOURCE_FILES})