//
// Created by adbhat on 10/16/16.
//

#include "RPCGateway.h"
# include <iostream>
using namespace std;

#define DEBUGLEVEL 1

//# include "NFSServer.h"
// Server side
// For calling NFSServer

//NFSServer nfsServer;


// Only fi->fh and fi->flags are ever used
void copyToThrift_fuseFileInfo(struct fuse_file_info *fi, struct thrift_fuse_file_info &tfi)
{
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
}

void copyFromThrift_fuseFileinfo(struct fuse_file_info *fi, thrift_fuse_file_info &tfi) {
    fi->fh = tfi.fh;
    fi->direct_io = tfi.direct_io;
    fi->fh_old = tfi.fh_old;
    fi->flags = tfi.flags;
}

void copyToThrift_stat(struct stat * stbuf, thrift_stat &tstbuf) {
    tstbuf.__glibc_reserved0 = stbuf->__glibc_reserved[0];
    tstbuf.__glibc_reserved1 = stbuf->__glibc_reserved[1];
    tstbuf.__glibc_reserved2 = stbuf->__glibc_reserved[2];
    tstbuf.__pad0 = stbuf->__pad0;

    tstbuf.st_blocks =	stbuf->st_blocks;
    tstbuf.st_blksize =	stbuf->st_blksize;

    tstbuf.st_dev =	stbuf->st_dev;
    tstbuf.st_gid =	stbuf->st_gid;
    tstbuf.st_ino =	stbuf->st_ino;
    tstbuf.st_mode =	stbuf->st_mode;

    tstbuf.st_nlink =	stbuf->st_nlink;
    tstbuf.st_rdev =	stbuf->st_rdev;
    tstbuf.st_size =	stbuf->st_size;
    tstbuf.st_uid =	stbuf->st_uid;

    tstbuf.st_atim.tv_nsec =	stbuf->st_atim.tv_nsec;
    tstbuf.st_ctim.tv_nsec =	stbuf->st_ctim.tv_nsec;
    tstbuf.st_mtim.tv_nsec =	stbuf->st_mtim.tv_nsec;

    tstbuf.st_atim.tv_sec =	stbuf->st_atim.tv_sec;
    tstbuf.st_ctim.tv_sec =	stbuf->st_ctim.tv_sec;
    tstbuf.st_mtim.tv_sec =	stbuf->st_mtim.tv_sec;
}

void copyFromthrift_stat(struct stat * stbuf, thrift_stat &tstbuf) {
    stbuf->__glibc_reserved[0] = tstbuf.__glibc_reserved0;
    stbuf->__glibc_reserved[1] = tstbuf.__glibc_reserved1;
    stbuf->__glibc_reserved[2] = tstbuf.__glibc_reserved2;
    stbuf->__pad0 = tstbuf.__pad0;


    stbuf->st_blocks =	tstbuf.st_blocks;
    stbuf->st_blksize =	tstbuf.st_blksize;
    stbuf->st_dev =	tstbuf.st_dev;
    stbuf->st_gid =	tstbuf.st_gid;
    stbuf->st_ino =	tstbuf.st_ino;
    stbuf->st_mode =	tstbuf.st_mode;
    stbuf->st_nlink =	tstbuf.st_nlink;
    stbuf->st_rdev =	tstbuf.st_rdev;
    stbuf->st_size =	tstbuf.st_size;
    stbuf->st_uid =	tstbuf.st_uid;

    stbuf->st_atim.tv_nsec = tstbuf.st_atim.tv_nsec;
    stbuf->st_ctim.tv_nsec = tstbuf.st_ctim.tv_nsec;
    stbuf->st_mtim.tv_nsec = tstbuf.st_mtim.tv_nsec;

    stbuf->st_atim.tv_sec = tstbuf.st_atim.tv_sec;
    stbuf->st_ctim.tv_sec = tstbuf.st_ctim.tv_sec;
    stbuf->st_mtim.tv_sec = tstbuf.st_mtim.tv_sec;
}

void copyToThrift_statvfs(struct statvfs * stbuf, thrift_statvfs tstbuf) {
    tstbuf.__f_spare0 = 	stbuf->__f_spare[0];
    tstbuf.__f_spare1 = 	stbuf->__f_spare[1];
    tstbuf.__f_spare2 = 	stbuf->__f_spare[2];
    tstbuf.__f_spare3 = 	stbuf->__f_spare[3];
    tstbuf.__f_spare4 = 	stbuf->__f_spare[4];
    tstbuf.__f_spare5 = 	stbuf->__f_spare[5];
    tstbuf.f_bavail = 	stbuf->f_bavail;
    tstbuf.f_bfree = 	stbuf->f_bfree;
    tstbuf.f_blocks = 	stbuf->f_blocks;
    tstbuf.f_bsize = 	stbuf->f_bsize;
    tstbuf.f_favail = 	stbuf->f_favail;
    tstbuf.f_ffree = 	stbuf->f_ffree;
    tstbuf.f_files = 	stbuf->f_files;
    tstbuf.f_flag = 	stbuf->f_flag;
    tstbuf.f_frsize = 	stbuf->f_frsize;
    tstbuf.f_fsid = 	stbuf->f_fsid;
    tstbuf.f_namemax = 	stbuf->f_namemax;
}

void copyFromThrift_statvfs(struct statvfs * stbuf, thrift_statvfs tstbuf) {
    stbuf->__f_spare[0] = 	tstbuf.__f_spare0;
    stbuf->__f_spare[1] = 	tstbuf.__f_spare1;
    stbuf->__f_spare[2] = 	tstbuf.__f_spare2;
    stbuf->__f_spare[3] = 	tstbuf.__f_spare3;
    stbuf->__f_spare[4] = 	tstbuf.__f_spare4;
    stbuf->__f_spare[5] = 	tstbuf.__f_spare5;
    stbuf->f_bavail = 	tstbuf.f_bavail;
    stbuf->f_bfree = 	tstbuf.f_bfree;
    stbuf->f_blocks = 	tstbuf.f_blocks;
    stbuf->f_bsize = 	tstbuf.f_bsize;
    stbuf->f_favail = 	tstbuf.f_favail;
    stbuf->f_ffree = 	tstbuf.f_ffree;
    stbuf->f_files = 	tstbuf.f_files;
    stbuf->f_flag = 	tstbuf.f_flag;
    stbuf->f_frsize = 	tstbuf.f_frsize;
    stbuf->f_fsid = 	tstbuf.f_fsid;
    stbuf->f_namemax = 	tstbuf.f_namemax;
}


int RPCGateway::xmp_unlink(string tpath) {
    const char * path = tpath.c_str();
    int retVal = nfsFuseServer.xmp_unlink(path);
    return retVal;
}

int RPCGateway::xmp_getattr(string tpath, thrift_stat &tstbuf) {
    const char * path = tpath.c_str();
    struct stat stbuf;
    copyFromthrift_stat(&stbuf, tstbuf);
    int retVal = nfsFuseServer.xmp_getattr(path, &stbuf);
    copyToThrift_stat(&stbuf, tstbuf);
    return retVal;
}

int RPCGateway::xmp_read(string tpath, string &tbuf, long int size, long int offset, thrift_fuse_file_info &tfi) {
    const char * path = tpath.c_str();
    char * buf = (char *)malloc(sizeof(char)*size);
    struct fuse_file_info fi;
    copyFromThrift_fuseFileinfo(&fi, tfi);
    int retVal = nfsFuseServer.xmp_read(path, buf, size, offset, &fi);
    copyToThrift_fuseFileInfo(&fi, tfi);
    tbuf = string(buf);
    return retVal;
}

int RPCGateway::xmp_write(string tpath, string &tbuf, long int size, long int offset, thrift_fuse_file_info &tfi) {
    const char * path = tpath.c_str();
    const char * buf = tbuf.c_str();
    struct fuse_file_info fi;
    copyFromThrift_fuseFileinfo(&fi, tfi);
    int retVal = nfsFuseServer.xmp_write(path, buf, size, offset, &fi);
    return retVal;
}

int RPCGateway::xmp_rename(string tfromName, string tto) {
    const char * fromName = tfromName.c_str();
    const char * to = tto.c_str();
    int retVal = nfsFuseServer.xmp_rename(fromName, to);
    return retVal;
}

int RPCGateway::xmp_mkdir(string tpath, int mode) {
    const char * path = tpath.c_str();
    int retVal = nfsFuseServer.xmp_mkdir(path, mode);
    return retVal;
}

int RPCGateway::xmp_rmdir(string tpath) {
    const char * path = tpath.c_str();
    int retVal = nfsFuseServer.xmp_rmdir(path);
    return retVal;
}

int RPCGateway::xmp_statfs(string tpath, thrift_statvfs &tstbuf) {
    const char * path = tpath.c_str();
    struct statvfs stbuf;
    copyFromThrift_statvfs(&stbuf, tstbuf);
    int retVal = nfsFuseServer.xmp_statfs(path, &stbuf);
    copyToThrift_statvfs(&stbuf, tstbuf);
    return retVal;
}

int RPCGateway::xmp_mknod(string tpath, mode_t mode, dev_t rdev) {
    const char * path = tpath.c_str();
    int retVal = nfsFuseServer.xmp_mknod(path, mode, rdev);
    return retVal;
}

int RPCGateway::xmp_access(string tpath, int mask) {
    const char * path = tpath.c_str();
    int retVal = nfsFuseServer.xmp_access(path, mask);
    return retVal;
}

int RPCGateway::xmp_readlink(string tpath, string &tbuf, size_t size) {
    const char * path = tpath.c_str();
    char * buf = (char *)malloc(sizeof(char)*size);
    int retVal = nfsFuseServer.xmp_readlink(path, buf, size);
    tbuf = string(buf);
    return retVal;
}

int RPCGateway::xmp_symlink(string tfrom, string tto) {
    const char * fromName = tfrom.c_str();
    const char * to = tto.c_str();
    int retVal = nfsFuseServer.xmp_symlink(fromName, to);
    return retVal;
}

int RPCGateway::xmp_link(string tfrom, string tto) {
    const char * fromName = tfrom.c_str();
    const char * to = tto.c_str();
    int retVal = nfsFuseServer.xmp_link(fromName, to);
    return retVal;
}

int RPCGateway::xmp_chmod(string tpath, mode_t mode) {
    const char * path = tpath.c_str();
    int retVal = nfsFuseServer.xmp_chmod(path, mode);
    return retVal;
}

int RPCGateway::xmp_chown(string tpath, uid_t uid, gid_t gid) {
    const char * path = tpath.c_str();
    int retVal = nfsFuseServer.xmp_chown(path, uid, gid);
    return retVal;
}

int RPCGateway::xmp_truncate(string tpath, off_t size) {
    const char * path = tpath.c_str();
    int retVal = nfsFuseServer.xmp_truncate(path, size);
    return retVal;
}

int RPCGateway::xmp_open(string tpath, thrift_fuse_file_info &tfi) {
    const char * path = tpath.c_str();
    struct fuse_file_info fi;
    copyFromThrift_fuseFileinfo(&fi, tfi);
    int retVal = nfsFuseServer.xmp_open(path, &fi);
    copyToThrift_fuseFileInfo(&fi, tfi);
    return retVal;
}

int RPCGateway::xmp_release(string tpath, thrift_fuse_file_info &tfi) {
    const char * path = tpath.c_str();
    struct fuse_file_info fi;
    copyFromThrift_fuseFileinfo(&fi, tfi);
    int retVal = nfsFuseServer.xmp_release(path, &fi);
    copyToThrift_fuseFileInfo(&fi, tfi);
    return retVal;
}

int RPCGateway::xmp_fsync(string tpath, int isdatasync, thrift_fuse_file_info &tfi) {
    const char * path = tpath.c_str();
    struct fuse_file_info fi;
    copyFromThrift_fuseFileinfo(&fi, tfi);
    int retVal = nfsFuseServer.xmp_fsync(path, isdatasync, &fi);
    copyToThrift_fuseFileInfo(&fi, tfi);
    return retVal;
}

//int main(int argc, char **argv) {
//    cout << "Hello World - RPCGateway Client" << endl;
//
//    RPCGateway rpcGateway;
//
//    rpcGateway.xmp_unlink("/u/a/d/adbhat/private/gitRepository/NFS_FUSE_Implementation/server_side/v1/temp.txt");
//
//
////    __fsblkcnt_t f1 = UINT64_MAX;
////    unsigned long int uli = f1;
////    long int li = uli;
////    unsigned long int uli2 = li;
////    cout << f1 << endl << uli << endl << li << endl << uli2;
//
//}