cmake_minimum_required(VERSION 3.6)
project(v1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES NFSServer.cpp NFSServer.h)

#-D_FILE_OFFSET_BITS=64 -pthread
set_source_files_properties(NFSServer.cpp PROPERTIES COMPILE_FLAGS "-D_FILE_OFFSET_BITS=64 -pthread" )

#-I
include_directories(/u/a/d/adbhat/Software/include/fuse)

add_executable(v1 NFSServer.cpp NFSServer.h)

# -L/u/a/d/adbhat/Software/lib -lfuse
find_library(FUSE_LIBRARY fuse HINTS /u/a/d/adbhat/Software/lib)
target_link_libraries(v1 PUBLIC ${FUSE_LIBRARY})
