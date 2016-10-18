//
// Created by adbhat on 10/16/16.
//

#include "RPCGateway.h"




//# include "NFSServer.h"
// Server side
// For calling NFSServer

//NFSServer nfsServer;

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

int RPCGateway::xmp_remove(const char *path) {

}

int RPCGateway::xmp_remove(string path) {

}