
# FUSE
FUSE_DIR = /u/a/d/adbhat/Software/include/fuse
INCS_DIRS_FUSE = -I${FUSE_DIR}
LIBS_DIRS_FUSE = -L/u/a/d/adbhat/Software/lib
LIBS_FUSE = -lfuse
CPP_OPTS_FUSE = -D_FILE_OFFSET_BITS=64 -pthread
CPP_OPTS = -Wall -O3

default: client

client: NFSClient.cpp
	g++ NFSClient.cpp NFSClient.h ${CPP_OPTS_FUSE} ${CPP_OPTS} -std=c++11 -o NFSClient.o ${INCS_DIRS_FUSE} ${LIBS_DIRS_FUSE} ${LIBS_FUSE}

clean:
	$(RM) -r NFSClient.o
