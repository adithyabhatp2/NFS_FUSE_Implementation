cmake_minimum_required(VERSION 3.6)
project(test_fuse)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES read_file.cpp)
add_executable(test_fuse ${SOURCE_FILES})