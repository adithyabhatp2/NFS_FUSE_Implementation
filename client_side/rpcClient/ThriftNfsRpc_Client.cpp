//
// Created by adbhat on 10/17/16.
//

#include "ThriftNfsRpc_Client.h"
#include <iostream>

using namespace std;

#define DEBUGLEVEL 1


ThriftNfsRpc_Client::ThriftNfsRpc_Client(char * serverHost, unsigned long serverPort) {
    this->hostName = strdup(serverHost);
    this->serverPort = serverPort;
}

int ThriftNfsRpc_Client::xmp_remove(string path) {

    boost::shared_ptr<TTransport> socket(new TSocket(hostName, serverPort));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    NfsRpcClient client(protocol);

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


int main(int argc, char **argv) {
    cout << "Hello World - Thrift Client" << endl;
    char * hostName = strdup("localhost");
    ThriftNfsRpc_Client rpcClient(hostName, 9090);
    rpcClient.xmp_remove("asd");
}