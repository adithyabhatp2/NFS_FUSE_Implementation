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



//int RPCGateway ::xmp_open(const char *path, struct fuse_file_info *fi)
//{
////string pathStr = ;
////    rpc_fuse_file_info = *fi;
////    rpcClient.xmp_open(pathStr, grpc_fuse_file_open)
//}
//
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
//    RPCGateway clientGateway(hostName, 9090);
//
//    clientGateway.xmp_remove("asd");
//}