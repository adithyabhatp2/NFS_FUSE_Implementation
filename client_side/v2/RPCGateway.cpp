//
// Created by adbhat on 10/16/16.
//

#include "RPCGateway.h"


#define DEBUGLEVEL 1

//# include "NFSServer.h"
// Server side
// For calling NFSServer

//NFSServer nfsServer;


RPCGateway::RPCGateway(char *serverHost, unsigned long serverPort) {

    if(DEBUGLEVEL <= 1) {
        cout << "RPCGateway Client Constructor: " << serverHost << "\t" << serverPort << endl;
    }

    this->rpcClient = ThriftNfsRpc_Client(serverHost, serverPort);
}



int RPCGateway ::xmp_open(const char *path, struct fuse_file_info *fi)
{
    string pathStr(path);
    thrift_fuse_file_info tfi;

    tfi.fh = fi->fh;
    tfi.direct_io = fi->direct_io;
    tfi.fh_old = fi->fh_old;
    tfi.flags = fi->flags;
    tfi.flock_release = fi->flock_release;
    tfi.flush = fi->flush;
    tfi.keep_cache = fi->keep_cache;
    tfi.lock_owner = fi->lock_owner;
    tfi.nonseekable = fi->nonseekable;
    tfi.padding = fi->padding;
    tfi.writepage = fi->writepage;

    int retVal = rpcClient.xmp_open(pathStr, tfi);

    fi->fh = tfi.fh;
    fi->direct_io = tfi.direct_io;
    fi->fh_old = tfi.fh_old;
    fi->flags = tfi.flags;
    //TODO

    return retVal;
}

//int RPCGateway :: xmp_open(Xmp_open_request open_request)
//{
//    char *path;
//    struct fuse_file_info file_info;
////    file_info.fh = ...
//    struct fuse_file_info *fi = &file_info;
//    return nfsServer.xmp_open(path, fi);
//}

// Client Side
int RPCGateway::xmp_remove(const char *path) {
    string pathStr(path);
    return rpcClient.xmp_remove(pathStr);
}

int RPCGateway::xmp_remove(string pathStr) {
    const char * path = pathStr.c_str();
    return 0;
}

//int main(int argc, char **argv) {
//    cout << "Hello World - RPCGateway Client" << endl;
//    char * hostName = strdup("localhost");
//
//
//    RPCGateway rpcGateway(hostName, 9090);
//
//    rpcGateway.xmp_remove("asd");
//}