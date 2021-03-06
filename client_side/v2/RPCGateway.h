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

    int xmp_create(const char *path, mode_t mode, struct fuse_file_info *fi);
    int xmp_unlink(const char *path);
    int xmp_getattr(const char *path, struct stat *stbuf);
    int xmp_setattr(const char *path, struct stat *stbuf);
    int xmp_read(const char *path, char *buf, size_t size, off_t offset,
                 struct fuse_file_info *fi);
    int xmp_write(const char *path, const char *buf, size_t size,
                  off_t offset, struct fuse_file_info *fi);
    int xmp_rename(const char *from, const char *to);
    int xmp_mkdir(const char *path, mode_t mode);
    int xmp_rmdir(const char *path);
    int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                    off_t offset, struct fuse_file_info *fi);
    int xmp_statfs(const char *path, struct statvfs *stbuf);

    int xmp_access(const char *path, int mask);
    int xmp_readlink(const char *path, char *buf, size_t size);
    int xmp_mknod(const char *path, mode_t mode, dev_t rdev);
    int xmp_symlink(const char *from, const char *to);
    int xmp_link(const char *from, const char *to);
    int xmp_chmod(const char *path, mode_t mode);
    int xmp_chown(const char *path, uid_t uid, gid_t gid);
    int xmp_truncate(const char *path, off_t size);
    int xmp_open(const char *path, struct fuse_file_info *fi);
    int xmp_release(const char *path, struct fuse_file_info *fi);
    int xmp_fsync(const char *path, int isdatasync, struct fuse_file_info *fi);

//    int xmp_mknod(const char *path, mode_t mode, dev_t rdev);



};


#endif //RPCGATEWAY_RPCGATEWAY_H
