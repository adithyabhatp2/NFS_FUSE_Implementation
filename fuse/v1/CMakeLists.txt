cmake_minimum_required(VERSION 3.6)
project(v1 C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES hello.cpp)

#-D_FILE_OFFSET_BITS=64
set_source_files_properties(hello.cpp PROPERTIES COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64" )

# -pthread

# -I/u/a/d/adbhat/Software/include/fuse
include_directories(/u/a/d/adbhat/Software/include/fuse ../gen-cpp)

add_executable(fuse ${SOURCE_FILES})




# -L/u/a/d/adbhat/Software/lib -lfuse

find_library(FUSE_LIBRARY fuse HINTS /u/a/d/adbhat/Software/lib)
target_link_libraries(fuse PUBLIC ${THRIFT_LIBRARY})

