# ref http://stackoverflow.com/questions/9956861/thrift-cpp-sample-code-compile-error

USR_DIR    =/usr
THRIFT_DIR =/unsup/thrift-0.9.3
BOOST_DIR  =/unsup/boost-1.58.0
INCS_DIRS  =-I${BOOST_DIR}/include -I${THRIFT_DIR}/include 
# original file has I${USR_DIR}/include -I${THRIFT_DIR}/include/thrift ${USR_DIR}/boost/1.49.0/include/boost
LIBS_DIRS  =-L${BOOST_DIR}/lib -L${THRIFT_DIR}/lib
CPP_DEFS   =-D=HAVE_CONFIG_H
CPP_OPTS   =-Wall -O
#CPP_OPTS   =-Wall
LIBS       =-lthrift

#service name from thrift file
GEN_SRC    = gen-cpp/Echo.cpp  \
             gen-cpp/echo_types.cpp
GEN_INC    = -Igen-cpp

default: server client

server: Echo_server.cpp
	g++ ${CPP_OPTS} ${CPP_DEFS} -o CppServer.o ${GEN_INC} ${INCS_DIRS} Echo_server.cpp ${GEN_SRC} ${LIBS_DIRS} ${LIBS}

client: Echo_client.cpp
	g++ ${CPP_OPTS} -std=c++11 ${CPP_DEFS} -o CppClient.o ${GEN_INC} ${INCS_DIRS} Echo_client.cpp ${GEN_SRC} ${LIBS_DIRS} ${LIBS}

clean:
	$(RM) -r CppClient CppServer

# -std=c++11 throws weird errors in server, about shared_ptr etc
