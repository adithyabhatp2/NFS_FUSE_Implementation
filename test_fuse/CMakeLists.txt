cmake_minimum_required(VERSION 3.6)
project(test_fuse)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES read_file_cpp.cpp)
add_executable(read_file_cpp ${SOURCE_FILES})
add_executable(read_file_c read_file_c.cpp)