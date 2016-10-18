USR_DIR    =/usr
THRIFT_DIR =/unsup/thrift-0.9.3
BOOST_DIR  =/unsup/boost-1.58.0

INCS_DIRS  =-I${BOOST_DIR}/include -I${THRIFT_DIR}/include
LIBS_DIRS  =-L${BOOST_DIR}/lib -L${THRIFT_DIR}/lib

CPP_DEFS   =-D=HAVE_CONFIG_H
CPP_OPTS   =-Wall -O3
LIBS       =-lthrift

#service name from thrift file
GEN_SRC    = gen-cpp/NfsRpc.cpp \
                gen-cpp/NfsRpc_constants.cpp \
                gen-cpp/NfsRpc_types.cpp

GEN_INC    = -Igen-cpp

default: server client

server:
	g++ ${CPP_OPTS} ${CPP_DEFS} -o ThriftServer.o ${GEN_INC} ${INCS_DIRS} ${GEN_SRC} NfsRpc_server.cpp ${LIBS_DIRS} ${LIBS}

client:
	g++ ${CPP_OPTS} -std=c++11 ${CPP_DEFS} -o ThriftClient.o ${GEN_INC} ${INCS_DIRS} ${GEN_SRC} ThriftNfsRpc_Client.cpp ThriftNfsRpc_Client.h ${LIBS_DIRS} ${LIBS}

clean:
	$(RM) -r ThriftClient.o ThriftServer.o

# -std=c++11 throws weird errors in server, about shared_ptr etc