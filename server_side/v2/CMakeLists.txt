cmake_minimum_required(VERSION 3.6)
project(nfsserver_v2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories(/unsup/thrift-0.9.3/include /unsup/boost-1.58.0/include gen-cpp)
include_directories(/u/a/d/adbhat/Software/include/fuse)

find_library(THRIFT_LIBRARY thrift HINTS /unsup/thrift-0.9.3/lib)

set(THRIFT_GEN_FILES gen-cpp/NfsRpc.cpp gen-cpp/NfsRpc_constants.cpp gen-cpp/NfsRpc_types.cpp)

set(FUSE_SERVER_FILES NfsFuseServer.cpp)
set_source_files_properties(NfsFuseServer.cpp PROPERTIES COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64 -pthread" )
#add_executable(nfsFuseServer ${FUSE_SERVER_FILES} ${THRIFT_GEN_FILES})
#target_link_libraries(nfsFuseServer PUBLIC ${THRIFT_LIBRARY})


set(GATEWAY_FILES RPCGateway.cpp RPCGateway.h)
set_source_files_properties(RPCGateway.cpp RPCGateway.h PROPERTIES COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64 -pthread -std=c++11" )
#add_executable(rpcGateway ${GATEWAY_FILES} gen-cpp/NfsRpc_types.cpp ${FUSE_SERVER_FILES})


set(WRITE_CACHE_ENTRY_FILES WriteCacheEntry.h WriteCacheEntry.cpp)
set(WRITE_CACHE_FILES WriteCache.h WriteCache.cpp ${WRITE_CACHE_ENTRY_FILES})

set_source_files_properties(WriteCache.cpp PROPERTIES COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64 -pthread")

set_source_files_properties(NfsRpc_server.cpp PROPERTIES COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64 -pthread" )
set(THRIFT_SERVER_FILES NfsRpc_server.cpp)


add_executable(thriftRpcServer ${THRIFT_SERVER_FILES} ${THRIFT_GEN_FILES} ${WRITE_CACHE_FILES} ${GATEWAY_FILES} ${FUSE_SERVER_FILES})
target_link_libraries(thriftRpcServer PUBLIC ${THRIFT_LIBRARY})
