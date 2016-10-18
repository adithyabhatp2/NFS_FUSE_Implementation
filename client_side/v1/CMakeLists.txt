cmake_minimum_required(VERSION 3.6)
project(rpcClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(THRIFT_CLIENT_FILES ThriftNfsRpc_Client.cpp ThriftNfsRpc_Client.h)


include_directories(/unsup/thrift-0.9.3/include /unsup/boost-1.58.0/include gen-cpp)
include_directories(/u/a/d/adbhat/Software/include/fuse)

#add_executable(thriftRpcClient ${CLIENT_FILES} gen-cpp/NfsRpc.cpp gen-cpp/NfsRpc_constants.cpp gen-cpp/NfsRpc_types.cpp)

add_executable(rpcClientGateway RPCGateway.cpp RPCGateway.h ${THRIFT_CLIENT_FILES} gen-cpp/NfsRpc.cpp gen-cpp/NfsRpc_constants.cpp gen-cpp/NfsRpc_types.cpp)

find_library(THRIFT_LIBRARY thrift HINTS /unsup/thrift-0.9.3/lib)
find_library(FUSE_LIBRARY fuse HINTS /u/a/d/adbhat/Software/lib)


#target_link_libraries(thriftRpcClient PUBLIC ${THRIFT_LIBRARY})
target_link_libraries(rpcClientGateway PUBLIC ${THRIFT_LIBRARY})
target_link_libraries(rpcClientGateway PUBLIC ${FUSE_LIBRARY})

set_source_files_properties(RPCGateway.cpp PROPERTIES COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64 -pthread -std=c++11" )


