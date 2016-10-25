cmake_minimum_required(VERSION 3.6)
project(v1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(FUSE_SERVER_FILES NfsFuseServer.cpp)
set_source_files_properties(NfsFuseServer.cpp PROPERTIES COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64 -pthread -std=c++11" )
add_executable(nfsFuseServer ${FUSE_SERVER_FILES})


set(GATEWAY_FILES RPCGateway.cpp RPCGateway.h)
set_source_files_properties(RPCGateway.cpp RPCGateway.h PROPERTIES COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64 -pthread -std=c++11" )
add_executable(rpcGateway ${GATEWAY_FILES} ${FUSE_SERVER_FILES})


set(THRIFT_SERVER_FILES NfsRpc_server.cpp)
set(THRIFT_GEN_FILES gen-cpp/NfsRpc.cpp gen-cpp/NfsRpc_constants.cpp gen-cpp/NfsRpc_types.cpp)



include_directories(/unsup/thrift-0.9.3/include /unsup/boost-1.58.0/include gen-cpp)
include_directories(/u/a/d/adbhat/Software/include/fuse)

find_library(THRIFT_LIBRARY thrift HINTS /unsup/thrift-0.9.3/lib)

add_executable(thriftRpcServer ${THRIFT_SERVER_FILES} ${THRIFT_GEN_FILES})
target_link_libraries(thriftRpcServer PUBLIC ${THRIFT_LIBRARY})
