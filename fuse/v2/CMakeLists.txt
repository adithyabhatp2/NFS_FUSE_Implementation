cmake_minimum_required(VERSION 3.6)
project(v3)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SOURCE_FILES gen-cpp/Echo.cpp gen-cpp/echo_types.cpp Echo_client.cpp Echo_server.cpp)

include_directories(/unsup/thrift-0.9.3/include /unsup/boost-1.58.0/include ../gen-cpp)

add_executable(CppServer Echo_server.cpp gen-cpp/Echo.cpp gen-cpp/echo_constants.cpp gen-cpp/echo_types.cpp)
add_executable(CppClient Echo_client.cpp  gen-cpp/Echo.cpp gen-cpp/echo_constants.cpp gen-cpp/echo_types.cpp)

find_library(THRIFT_LIBRARY thrift HINTS /unsup/thrift-0.9.3/lib)

target_link_libraries(CppServer PUBLIC ${THRIFT_LIBRARY})
target_link_libraries(CppClient PUBLIC ${THRIFT_LIBRARY})

set_source_files_properties( Echo_client.cpp PROPERTIES COMPILE_FLAGS "-std=c++11" )
