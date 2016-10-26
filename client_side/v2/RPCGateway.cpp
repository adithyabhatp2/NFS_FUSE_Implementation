//
// Created by adbhat on 10/16/16.
//

#include "RPCGateway.h"


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

RPCGateway::RPCGateway(char *serverHost, unsigned long serverPort) {

    if(DEBUGLEVEL <= 1) {
        cout << "RPCGateway Client Constructor: " << serverHost << "\t" << serverPort << endl;
    }

    this->rpcClient = ThriftNfsRpc_Client(serverHost, serverPort);
}



int RPCGateway::xmp_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
    string tpath(path);
    thrift_fuse_file_info tfi;

    tfi.flags = fi->flags;

    return rpcClient.xmp_create(path, mode, tfi);
}

// Client Side
int RPCGateway::xmp_unlink(const char *path) {
    string pathStr(path);
    return rpcClient.xmp_unlink(pathStr);
}

int RPCGateway::xmp_getattr(const char *path, struct stat *stbuf) {
    int retVal = -1;
    string tpath(path);
    thrift_stat tstbuf;
    copyToThrift_stat(stbuf, tstbuf);
    retVal = rpcClient.xmp_getattr(tpath, tstbuf); //TODO fix
    if(retVal!=-1) {
        copyFromthrift_stat(stbuf, tstbuf);
    }
    return retVal;
}

int RPCGateway::xmp_setattr(const char *path, struct stat *stbuf) {
    int retVal = -1;
    string tpath(path);
    thrift_stat tstbuf;
    copyToThrift_stat(stbuf, tstbuf);
    retVal = rpcClient.xmp_getattr(tpath, tstbuf);
    copyFromthrift_stat(stbuf, tstbuf);
    return retVal;
}

int RPCGateway::xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    int retVal = -1;
    string tpath(path);
    string tbuf;
    thrift_fuse_file_info tfi;
    copyToThrift_fuseFileInfo(fi, tfi);
    retVal = rpcClient.xmp_read(tpath, tbuf, size, offset, tfi);
    strncpy(buf, tbuf.c_str(), size);

    return retVal;
}

int RPCGateway::xmp_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    int retVal = -1;
    string tpath(path);
    string tbuf(buf);
    thrift_fuse_file_info tfi;
    copyToThrift_fuseFileInfo(fi, tfi);
    retVal = rpcClient.xmp_write(tpath, tbuf, size, offset, tfi);
    return retVal;
}

int RPCGateway::xmp_rename(const char *from, const char *to) {
    string tfrom(from);
    string tto(to);
    return rpcClient.xmp_rename(tfrom, tto);
}

int RPCGateway::xmp_mkdir(const char *path, mode_t mode) {
    string tpath(path);
    return rpcClient.xmp_mkdir(tpath, mode);
}

int RPCGateway::xmp_rmdir(const char *path) {
    string tpath(path);
    return rpcClient.xmp_rmdir(tpath);
}

int RPCGateway::xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset,
                            struct fuse_file_info *fi) {
    int retVal = -1;
    string tpath(path);
    string tbuf;
    thrift_fuse_file_info tfi;
    thrift_readdir_reply reply;
    copyToThrift_fuseFileInfo(fi, tfi);

    rpcClient.xmp_readdir(tpath, offset, tfi, reply);

    for (thrift_dir_entry de : reply.dir_entries) {
        struct stat st;
        memset(&st, 0, sizeof(st));
        st.st_ino = de.d_ino;
        st.st_mode = de.d_type << 12;
        if (filler(buf, de.d_name.c_str(), &st, 0))
            break;
    }

    return retVal;
}

int RPCGateway::xmp_statfs(const char *path, struct statvfs *stbuf) {
    int retVal = -1;
    string tpath(path);
    thrift_statvfs tstbuf;
    copyToThrift_statvfs(stbuf, tstbuf);
    retVal = rpcClient.xmp_statfs(tpath, tstbuf); //TODO fix
    copyFromThrift_statvfs(stbuf, tstbuf);
    return retVal;
}


int RPCGateway::xmp_readlink(const char *path, char *buf, size_t size) {
    int retVal = -1;
    string tpath(path);
    thrift_readlink_reply reply;
    string tbuf(buf);

    rpcClient.xmp_readlink(reply, tpath, tbuf, size);
    retVal = reply.retVal;
    strncpy(buf, reply.tbuf.c_str(), size);
    return retVal;
}

int RPCGateway::xmp_access(const char *path, int mask){
    string tpath(path);
    return rpcClient.xmp_access(tpath, mask);
}

int RPCGateway::xmp_mknod(const char *path, mode_t mode, dev_t rdev){
    string tpath(path);
    return rpcClient.xmp_mknod(tpath, mode, rdev);
}

int RPCGateway::xmp_symlink(const char *from, const char *to){
    int retVal = -1;
    string fromPath(from);
    string toPath(to);
    retVal = rpcClient.xmp_symlink(fromPath, toPath);
    return retVal;
}

int RPCGateway::xmp_link(const char *from, const char *to){
    int retVal = -1;
    string fromPath(from);
    string toPath(to);
    retVal = rpcClient.xmp_link(fromPath, toPath);
    return retVal;
}

int RPCGateway::xmp_chmod(const char *path, mode_t mode){
    int retVal = -1;
    string tpath(path);
    retVal = rpcClient.xmp_chmod(tpath, mode);
    return retVal;
}

int RPCGateway::xmp_chown(const char *path, uid_t uid, gid_t gid){
    int retVal = -1;
    string tpath(path);
    retVal = rpcClient.xmp_chown(tpath, uid, gid);
    return retVal;
}

int RPCGateway::xmp_truncate(const char *path, off_t size){
    int retVal = -1;
    string tpath(path);
    retVal = rpcClient.xmp_truncate(tpath, size);
    return retVal;
}

int RPCGateway::xmp_open(const char *path, struct fuse_file_info *fi)
{
    string pathStr(path);
    thrift_fuse_file_info tfi;

    copyToThrift_fuseFileInfo(fi, tfi);
    int retVal = rpcClient.xmp_open(pathStr, tfi);
    copyFromThrift_fuseFileinfo(fi, tfi);

    return retVal;
}

int RPCGateway::xmp_release(const char *path, struct fuse_file_info *fi) {
    string pathStr(path);
    thrift_fuse_file_info tfi;

    copyToThrift_fuseFileInfo(fi, tfi);
    int retVal = rpcClient.xmp_release(pathStr, tfi);
    copyFromThrift_fuseFileinfo(fi, tfi);

    return retVal;
}

int RPCGateway::xmp_fsync(const char *path, int isdatasync, struct fuse_file_info *fi){
    string pathStr(path);
    thrift_fuse_file_info tfi;

    copyToThrift_fuseFileInfo(fi, tfi);
    int retVal = rpcClient.xmp_fsync(pathStr, isdatasync, tfi);
    copyFromThrift_fuseFileinfo(fi, tfi);

    return retVal;
}



//int main(int argc, char **argv) {
//    cout << "Hello World - RPCGateway Client" << endl;
//    char * hostName = strdup("localhost");
//
//
//    RPCGateway rpcGateway(hostName, 9090);
//
//    rpcGateway.xmp_unlink("asd");
//}