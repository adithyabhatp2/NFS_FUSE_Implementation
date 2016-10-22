cmake_minimum_required(VERSION 3.6)
project(rpcClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(FUSE_CLIENT_FILES NFSClient.cpp)
set(GATEWAY_CLIENT_FILES RPCGateway.cpp RPCGateway.h)
set(THRIFT_CLIENT_FILES ThriftNfsRpc_Client.cpp ThriftNfsRpc_Client.h)
set(THRIFT_GEN_FILES gen-cpp/NfsRpc.cpp gen-cpp/NfsRpc_constants.cpp gen-cpp/NfsRpc_types.cpp)

include_directories(/unsup/thrift-0.9.3/include /unsup/boost-1.58.0/include gen-cpp)
include_directories(/u/a/d/adbhat/Software/include/fuse)

add_executable(nfsFuseClient ${FUSE_CLIENT_FILES} ${GATEWAY_CLIENT_FILES} ${THRIFT_CLIENT_FILES} ${THRIFT_GEN_FILES})

find_library(THRIFT_LIBRARY thrift HINTS /unsup/thrift-0.9.3/lib)
find_library(FUSE_LIBRARY fuse HINTS /u/a/d/adbhat/Software/lib)

target_link_libraries(nfsFuseClient PUBLIC ${THRIFT_LIBRARY})
target_link_libraries(nfsFuseClient PUBLIC ${FUSE_LIBRARY})

set_source_files_properties(NFSClient.cpp RPCGateway.cpp PROPERTIES COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64 -pthread -std=c++11" )


add_executable(thriftRpcServer NfsRpc_server.cpp ${THRIFT_GEN_FILES})
target_link_libraries(thriftRpcServer PUBLIC ${THRIFT_LIBRARY})