cmake_minimum_required(VERSION 3.6)
project(rpcGateway)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES RPCGateway.cpp RPCGateway.h)

set_source_files_properties(RPCGateway.cpp PROPERTIES COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64 -pthread" )
include_directories(/u/a/d/adbhat/Software/include/fuse)
find_library(FUSE_LIBRARY fuse HINTS /u/a/d/adbhat/Software/lib)

add_executable(rpcGateway ${SOURCE_FILES} RPCGateway.cpp RPCGateway.h)

target_link_libraries(rpcGateway PUBLIC ${FUSE_LIBRARY})
