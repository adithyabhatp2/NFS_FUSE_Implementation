//
// Created by adbhat on 10/16/16.
//

#ifndef RPCGATEWAY_RPCGATEWAY_H
#define RPCGATEWAY_RPCGATEWAY_H

#ifdef HAVE_CONFIG_H
//#include <config.h>
#endif

#ifdef linux
/* For pread()/pwrite()/utimensat() */
#define _XOPEN_SOURCE 700
#endif

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#ifdef HAVE_SETXATTR
#include <sys/xattr.h>
#endif

# include <iostream>
#include "ThriftNfsRpc_Client.h"

using namespace std;

//# include grpc protobuf headers
// Client side
// For converting to GRPC format


class RPCGateway {
public:

    RPCGateway(char *, unsigned long);
//    RPCGateway(ThriftNfsRpc_Client);

    ThriftNfsRpc_Client rpcClient;

    // Client - Serialization
//    int xmp_open(const char *path, struct fuse_file_info *fi);
//    int xmp_access(const char *path, int mask);
//    int xmp_mknod(const char *path, mode_t mode, dev_t rdev);
    int xmp_remove(const char *path) ;
//    int xmp_getattr(const char *path, struct stat *stbuf);
//    int xmp_setattr(const char *path, struct stat *stbuf);
//    int xmp_read(const char *path, char *buf, size_t size, off_t offset,
//                 struct fuse_file_info *fi);
//    int xmp_write(const char *path, const char *buf, size_t size,
//                  off_t offset, struct fuse_file_info *fi);
//    int xmp_rename(const char *from, const char *to);
//    int xmp_mkdir(const char *path, mode_t mode);
//    int xmp_rmdir(const char *path);
//    int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
//                    off_t offset, struct fuse_file_info *fi);
//    int xmp_statfs(const char *path, struct statvfs *stbuf);

    // Deserialization
//    int xmp_open(Xmp_open_request);
//    int xmp_access(Xmp_access_request);
//    int xmp_mknod(Xmp_mknod_request);
    int xmp_remove(string path) ;
//    int xmp_getattr(Xmp_getattr_request);
//    int xmp_setattr(Xmp_setattr_request);
//    int xmp_read(Xmp_read_request);
//    int xmp_write(Xmp_write_request);
//    int xmp_rename(Xmp_rename_request);
//    int xmp_mkdir(Xmp_mkdir_request);
//    int xmp_rmdir(Xmp_rmdir_request);
//    int xmp_readdir(Xmp_readdir_request);
//    int xmp_statfs(Xmp_statfs_request);

};


#endif //RPCGATEWAY_RPCGATEWAY_H
