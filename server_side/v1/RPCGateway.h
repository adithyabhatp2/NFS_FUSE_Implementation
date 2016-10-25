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
#include "gen-cpp/NfsRpc_types.h"
#include "NfsFuseServer.h"


class RPCGateway {
public:

    NfsFuseServer nfsFuseServer;

    // Deserialization

    int xmp_unlink(std::string tpath) ;
    int xmp_getattr(std::string tpath, thrift_stat &tstbuf);

    int xmp_read(std::string tpath, std::string &tbuf, long int size, long int offset, thrift_fuse_file_info &tfi);
    int xmp_write(std::string tpath, std::string &tbuf, long int size, long int offset, thrift_fuse_file_info &tfi);
    int xmp_rename(std::string tfromName, std::string tto);
    int xmp_mkdir(std::string tpath, int mode);
    int xmp_rmdir(std::string tpath);
    int xmp_statfs(std::string tpath, thrift_statvfs &tstbuf);

    int xmp_access(std::string tpath, int mask);
    int xmp_readlink(std::string tpath, std::string &tbuf, size_t size);
    int xmp_mknod(std::string tpath, mode_t mode, dev_t rdev);
    int xmp_symlink(std::string tfrom, std::string tto);
    int xmp_link(std::string tfrom, std::string tto);
    int xmp_chmod(std::string tpath, mode_t mode);
    int xmp_chown(std::string tpath, uid_t uid, gid_t gid);
    int xmp_truncate(std::string tpath, off_t size);
    int xmp_open(std::string tpath, thrift_fuse_file_info &tfi);
    int xmp_release(std::string tpath, thrift_fuse_file_info &tfi);
    int xmp_fsync(std::string tpath, int isdatasync, thrift_fuse_file_info &tfi);
    
};


#endif //RPCGATEWAY_RPCGATEWAY_H
