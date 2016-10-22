USR_DIR    =/usr
THRIFT_DIR =/unsup/thrift-0.9.3
BOOST_DIR  =/unsup/boost-1.58.0

FUSE_INC_DIRS =-I/u/a/d/adbhat/Software/include/fuse
THRIFT_GEN_INC_DIR =-Igen-cpp
THRIFT_INC_DIRS  =-I${BOOST_DIR}/include -I${THRIFT_DIR}/include

FUSE_LIBS_DIRS =-L/u/a/d/adbhat/Software/lib
THRIFT_LIBS_DIRS  =-L${BOOST_DIR}/lib -L${THRIFT_DIR}/lib

LIBS       =-lthrift -lfuse

FUSE_CLIENT_FILES = NFSClient.cpp
GATEWAY_CLIENT_FILES = RPCGateway.cpp RPCGateway.h
THRIFT_CLIENT_FILES = ThriftNfsRpc_Client.cpp ThriftNfsRpc_Client.h
THRIFT_GEN_FILES = gen-cpp/NfsRpc.cpp gen-cpp/NfsRpc_constants.cpp gen-cpp/NfsRpc_types.cpp

CPP_OPTS_FUSE =-D_FILE_OFFSET_BITS=64 -pthread -std=c++11
CPP_DEFS   =-D=HAVE_CONFIG_H
CPP_OPTS   =-Wall -O3



default: client rpcserver

rpcserver:
	g++ ${CPP_OPTS} ${CPP_DEFS} -o ThriftServer.o ${THRIFT_GEN_INC_DIR} ${THRIFT_INC_DIRS} ${THRIFT_GEN_FILES} NfsRpc_server.cpp ${THRIFT_LIBS_DIRS} -lthrift

client:
	g++ ${CPP_OPTS} ${CPP_OPTS_FUSE} ${CPP_DEFS} -o fuseClient.o \
	    ${FUSE_CLIENT_FILES} ${GATEWAY_CLIENT_FILES} ${THRIFT_CLIENT_FILES} ${THRIFT_GEN_FILES} \
	    ${THRIFT_INC_DIRS} ${FUSE_INC_DIRS} ${THRIFT_GEN_INC_DIR} \
        ${THRIFT_LIBS_DIRS} ${FUSE_LIBS_DIRS} \
        ${LIBS}

clean:
	$(RM) -r fuseClient.o

# -std=c++11 throws weird errors in server, about shared_ptr etc
# after doing thrift --gen NfsRpc.thrift,
# search for class NfsRpcClient[a-z,A-Z,\s,:,{]+public:
# rplce with class NfsRpcClient[a-z,A-Z,\s,:,{]+public:$NfsRpcClient(){}