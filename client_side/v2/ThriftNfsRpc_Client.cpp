//
// Created by adbhat on 10/17/16.
//

#include "ThriftNfsRpc_Client.h"
#include <iostream>

using namespace std;

#define DEBUGLEVEL 1


ThriftNfsRpc_Client::ThriftNfsRpc_Client(char *serverHost, unsigned long serverPort) {
    if (DEBUGLEVEL <= 1) {
        cout << "ThriftNfsRpc_Client Constructor: " << serverHost << "\t" << serverPort << endl;
    }
    this->hostName = strdup(serverHost);
    this->serverPort = serverPort;

    this->socket = boost::shared_ptr<TTransport>(new TSocket(hostName, serverPort));
    this->transport = boost::shared_ptr<TTransport>(new TBufferedTransport(socket));
    this->protocol = boost::shared_ptr<TProtocol>(new TBinaryProtocol(transport));

    this->client = NfsRpcClient(protocol);
}


ThriftNfsRpc_Client::ThriftNfsRpc_Client() {
    if (DEBUGLEVEL <= 1) {
        cout << "ThriftNfsRpc_Client Default EMPTY Constructor: " << endl;
    }
}


int ThriftNfsRpc_Client::xmp_create(string path, mode_t mode, thrift_fuse_file_info &fi) {
    int retVal = -1;

    transport->open();
    retVal = client.xmp_create(path, mode, fi);
    transport->close();

    fi.fh = retVal;
    return retVal;
}


int ThriftNfsRpc_Client::xmp_unlink(string path) {

    int retVal = -1;

    try {
        transport->open();
        retVal = client.xmp_unlink(path);

        if (DEBUGLEVEL) {
            cout << "xmp_unlink retval in thrift client: " << retVal << endl;
        }
        transport->close();

    } catch (TException &tx) {
        cout << "ERROR: " << tx.what() << endl;
    }
    return retVal;
}


int ThriftNfsRpc_Client::xmp_getattr(string path, thrift_stat &stbuf) {

    thrift_getattr_reply reply;

    transport->open();
    client.xmp_getattr(reply, path, stbuf);
    transport->close();

    return reply.retVal;
}

int ThriftNfsRpc_Client::xmp_setattr(string path, thrift_stat &stbuf) {
    int retVal = -1;
    transport->open();
    retVal = client.xmp_setattr(path, stbuf);
    transport->close();
    return retVal;
}

int ThriftNfsRpc_Client::xmp_read(string path, string &buf, long int size, long int offset,
                                  thrift_fuse_file_info &fi) {
    thrift_read_reply reply;
    transport->open();
    client.xmp_read(reply, path, buf, size, offset, fi );
    transport->close();
    return reply.retVal;

}

int ThriftNfsRpc_Client::xmp_write(string path, string &buf, long int size, long int offset,
                                   thrift_fuse_file_info &fi) {
    int retVal = -1;
    transport->open();
    retVal = client.xmp_write(path, buf, size, offset, fi);
    transport->close();
    return retVal;
}

int ThriftNfsRpc_Client::xmp_rename(string fromName, string to) {
    int retVal = -1;
    transport->open();
    retVal = client.xmp_rename(fromName, to);
    transport->close();
    return retVal;
}

int ThriftNfsRpc_Client::xmp_mkdir(string path, int mode) {
    int retVal = -1;
    transport->open();
    retVal = client.xmp_mkdir(path, mode);
    transport->close();
    return retVal;
}

int ThriftNfsRpc_Client::xmp_rmdir(string path) {
    int retVal = -1;
    transport->open();
    retVal = client.xmp_rmdir(path);
    transport->close();
    return retVal;
}

int ThriftNfsRpc_Client::xmp_statfs(string path, thrift_statvfs &stbuf) {
    thrift_statfs_reply reply;
    transport->open();
    client.xmp_statfs(reply, path, stbuf);
    transport->close();
    return reply.retVal;
}

//int ThriftNfsRpc_Client::xmp_readdir

int ThriftNfsRpc_Client::xmp_open(string path, thrift_fuse_file_info &fi) {

    thrift_open_reply open_reply;

    try {

        transport->open();
        client.xmp_open(open_reply, path, fi);

        cout << "thrift cli : xmp_open: retVal" << open_reply.retVal << endl;
        cout << "thrift cli : xmp_open: fd" << open_reply.tfi.fh << endl;
        fi = open_reply.tfi;

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
//    rpcClient.xmp_unlink("asd");
//}