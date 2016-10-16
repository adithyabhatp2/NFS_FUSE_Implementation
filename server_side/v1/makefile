
# FUSE
FUSE_DIR = /u/a/d/adbhat/Software/include/fuse
INCS_DIRS_FUSE = -I${FUSE_DIR}
LIBS_DIRS_FUSE = -L/u/a/d/adbhat/Software/lib
LIBS_FUSE = -lfuse
CPP_OPTS_FUSE = -D_FILE_OFFSET_BITS=64 -pthread
CPP_OPTS = -Wall -O3

default: server

server: NFSServer.cpp
	g++ NFSServer.cpp NFSServer.h ${CPP_OPTS_FUSE} ${CPP_OPTS} -std=c++11 -o NFSServer.o ${INCS_DIRS_FUSE} ${LIBS_DIRS_FUSE} ${LIBS_FUSE}

clean:
	$(RM) -r NFSServer.o


