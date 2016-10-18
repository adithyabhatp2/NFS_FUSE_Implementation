//
// Created by adbhat on 10/17/16.
//

#ifndef RPCCLIENT_NFSRPC_CLIENT_H
#define RPCCLIENT_NFSRPC_CLIENT_H

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <vector>
#include "gen-cpp/NfsRpc.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

class ThriftNfsRpc_Client {
public:

    char * hostName;
    unsigned long int serverPort;

    boost::shared_ptr<TTransport> socket;
    boost::shared_ptr<TProtocol> protocol;
    boost::shared_ptr<TTransport> transport;

    NfsRpcClient client;

    ThriftNfsRpc_Client();
    ThriftNfsRpc_Client(char *, unsigned long);

    int xmp_remove(string path);


    int xmp_open(string path, thrift_fuse_file_info fi);

};


#endif //RPCCLIENT_NFSRPC_CLIENT_H
