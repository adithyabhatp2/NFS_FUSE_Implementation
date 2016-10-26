
THRIFT_DIR =/unsup/thrift-0.9.3
BOOST_DIR  =/unsup/boost-1.58.0

FUSE_SERVER_FILES = NfsFuseServer.cpp
GATEWAY_FILES = RPCGateway.cpp RPCGateway.h
THRIFT_SERVER_FILES = NfsRpc_server.cpp
THRIFT_GEN_FILES = gen-cpp/NfsRpc.cpp gen-cpp/NfsRpc_constants.cpp gen-cpp/NfsRpc_types.cpp

FUSE_INC_DIRS =-I/u/a/d/adbhat/Software/include/fuse
THRIFT_INC_DIRS  =-I${BOOST_DIR}/include -I${THRIFT_DIR}/include
THRIFT_GEN_INC_DIR =-Igen-cpp

FUSE_LIBS_DIRS =-L/u/a/d/adbhat/Software/lib
THRIFT_LIBS_DIRS  =-L${BOOST_DIR}/lib -L${THRIFT_DIR}/lib

LIBS       =-lthrift -lfuse
# lfuse unnecessary? ditto haveconfig


CPP_OPTS_FUSE =-D_FILE_OFFSET_BITS=64 -pthread
CPP_OPTS   =-Wall -O3
CPP_DEFS   =-D=HAVE_CONFIG_H
CPP_OPTS_C11 = -std=c++11


default: server

server:
	g++ ${CPP_OPTS} ${CPP_OPTS_FUSE} ${CPP_DEFS} -o server.o \
	    ${THRIFT_SERVER_FILES} ${THRIFT_GEN_FILES} ${GATEWAY_FILES} ${FUSE_SERVER_FILES} \
	    ${THRIFT_INC_DIRS} ${FUSE_INC_DIRS} ${THRIFT_GEN_INC_DIR} \
        ${THRIFT_LIBS_DIRS} ${FUSE_LIBS_DIRS} \
        ${LIBS}

#unverified gateway build
gateway:
	g++ ${CPP_OPTS} ${CPP_OPTS_FUSE} ${CPP_OPTS_C11} ${CPP_DEFS} -o gateway.o \
	    ${GATEWAY_FILES} ${FUSE_SERVER_FILES} ${THRIFT_GEN_FILES} \
	    ${THRIFT_GEN_INC_DIR} ${FUSE_INC_DIRS} ${THRIFT_INC_DIRS} \
	    ${THRIFT_LIBS_DIRS} ${FUSE_LIBS_DIRS} \
	    ${LIBS}

fuseServer:
	g++ ${CPP_OPTS} ${CPP_OPTS_FUSE} ${CPP_OPTS_C11} ${CPP_DEFS} -o fuseServer.o \
	    ${FUSE_SERVER_FILES} ${THRIFT_GEN_FILES} \
	    ${THRIFT_GEN_INC_DIR} ${FUSE_INC_DIRS} ${THRIFT_INC_DIRS} \
	    ${THRIFT_LIBS_DIRS} ${FUSE_LIBS_DIRS} \
	    ${LIBS}

clean:
	$(RM) -r *.o

# -std=c++11 throws weird errors in server, about shared_ptr etc
# after doing thrift --gen NfsRpc.thrift,
# search for class NfsRpcClient[a-z,A-Z,\s,:,{]+public:
# rplce with class NfsRpcClient[a-z,A-Z,\s,:,{]+public:$NfsRpcClient(){}