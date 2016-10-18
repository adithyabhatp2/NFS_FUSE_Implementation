//
// Created by adbhat on 10/17/16.
//

#include "ThriftNfsRpc_Client.h"
#include <iostream>

using namespace std;

#define DEBUGLEVEL 1


ThriftNfsRpc_Client::ThriftNfsRpc_Client(char * serverHost, unsigned long serverPort) {
    if(DEBUGLEVEL <= 1) {
        cout << "ThriftNfsRpc_Client Constructor: " << serverHost << "\t" << serverPort << endl;
    }
    this->hostName = strdup(serverHost);
    this->serverPort = serverPort;

    this->socket = boost::shared_ptr<TTransport>(new TSocket(hostName, serverPort));
    this->transport = boost::shared_ptr<TTransport>(new TBufferedTransport(socket));
    this->protocol = boost::shared_ptr<TProtocol>(new TBinaryProtocol(transport));

    this->client = NfsRpcClient(protocol);
}

/// Dummy constructor
/// \return
ThriftNfsRpc_Client::ThriftNfsRpc_Client() {
    if(DEBUGLEVEL <= 1) {
        cout << "ThriftNfsRpc_Client Default EMPTY Constructor: " <<  endl;
    }
}


int ThriftNfsRpc_Client::xmp_remove(string path) {

    int retVal = -1;

    try {

        transport->open();
        retVal = client.xmp_remove(path);

        if (DEBUGLEVEL) {
            cout << "xmp_remove: " << retVal << endl;
        }
        transport->close();

    } catch (TException &tx) {
        cout << "ERROR: " << tx.what() << endl;
    }
    return retVal;
}


int ThriftNfsRpc_Client::xmp_open(string path, thrift_fuse_file_info fi) {

    thrift_open_reply open_reply;

    try {

        transport->open();
        client.xmp_open(open_reply, path, fi);

        if (DEBUGLEVEL) {
            cout << "xmp_open: retVal" << open_reply.retVal << endl;
            cout << "xmp_open: fd" << open_reply.fi.fh << endl;
        }
        transport->close();

    } catch (TException &tx) {
        cout << "ERROR: " << tx.what() << endl;
    }
    return open_reply.retVal;
}



//int main(int argc, char **argv) {
//    cout << "Hello World - Thrift Client" << endl;
//    char * hostName = strdup("localhost");
//    ThriftNfsRpc_Client rpcClient(hostName, 9090);
//    rpcClient.xmp_remove("asd");
//}