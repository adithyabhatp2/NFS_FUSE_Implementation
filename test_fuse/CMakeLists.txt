cmake_minimum_required(VERSION 3.6)
project(test_fuse)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


add_executable(read_file_c read_file_fd.cpp)
add_executable(read_file_cpp read_file_cpp)
add_executable(write_file_c write_file_fd.cpp)