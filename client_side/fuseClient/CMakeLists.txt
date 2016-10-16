cmake_minimum_required(VERSION 3.6)
project(fuseClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES NFSClient.h NFSClient.cpp)

set_source_files_properties(NFSClient.cpp PROPERTIES COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64 -pthread" )
include_directories(/u/a/d/adbhat/Software/include/fuse)
find_library(FUSE_LIBRARY fuse HINTS /u/a/d/adbhat/Software/lib)

add_executable(fuseClient ${SOURCE_FILES})

target_link_libraries(fuseClient PUBLIC ${FUSE_LIBRARY})
