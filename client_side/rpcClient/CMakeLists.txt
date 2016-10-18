cmake_minimum_required(VERSION 3.6)
project(rpcClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SERVER_FILES NfsRpc_server.cpp)
set(CLIENT_FILES ThriftNfsRpc_Client.cpp ThriftNfsRpc_Client.h)


include_directories(/unsup/thrift-0.9.3/include /unsup/boost-1.58.0/include gen-cpp)

add_executable(thriftRpcServer ${SERVER_FILES} gen-cpp/NfsRpc.cpp gen-cpp/NfsRpc_constants.cpp gen-cpp/NfsRpc_types.cpp)
add_executable(thriftRpcClient ${CLIENT_FILES} gen-cpp/NfsRpc.cpp gen-cpp/NfsRpc_constants.cpp gen-cpp/NfsRpc_types.cpp)


find_library(THRIFT_LIBRARY thrift HINTS /unsup/thrift-0.9.3/lib)

target_link_libraries(thriftRpcServer PUBLIC ${THRIFT_LIBRARY})
target_link_libraries(thriftRpcClient PUBLIC ${THRIFT_LIBRARY})

set_source_files_properties(ThriftNfsRpc_Client.cpp PROPERTIES COMPILE_FLAGS "-std=c++11" )