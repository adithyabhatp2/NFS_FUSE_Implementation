//
// Created by adbhat on 10/17/16.
//

#include "ThriftNfsRpc_Client.h"
#include <iostream>

using namespace std;

#define DEBUGLEVEL 1


void copyThriftStat(thrift_stat& first, thrift_stat& other) {
    first.st_dev = other.st_dev;
    first.st_ino = other.st_ino;
    first.st_mode = other.st_mode;
    first.st_nlink = other.st_nlink;
    first.st_uid = other.st_uid;
    first.st_gid = other.st_gid;
    first.__pad0 = other.__pad0;
    first.st_size = other.st_size;
    first.st_blksize = other.st_blksize;
    first.st_blocks = other.st_blocks;
    first.st_atim = other.st_atim;
    first.st_mtim = other.st_mtim;
    first.st_ctim = other.st_ctim;
    first.__glibc_reserved0 = other.__glibc_reserved0;
    first.__glibc_reserved1 = other.__glibc_reserved1;
    first.__glibc_reserved2 = other.__glibc_reserved2;
    first.st_rdev = other.st_rdev;
    first.__isset = other.__isset;
}

void copyThriftStatvfs(thrift_statvfs& first, thrift_statvfs& other) {
    first.f_bsize = other.f_bsize;
    first.f_frsize = other.f_frsize;
    first.f_blocks = other.f_blocks;
    first.f_bfree = other.f_bfree;
    first.f_bavail = other.f_bavail;
    first.f_files = other.f_files;
    first.f_ffree = other.f_ffree;
    first.f_favail = other.f_favail;
    first.f_fsid = other.f_fsid;
    first.f_flag = other.f_flag;
    first.f_namemax = other.f_namemax;
    first.__f_spare0 = other.__f_spare0;
    first.__f_spare1 = other.__f_spare1;
    first.__f_spare2 = other.__f_spare2;
    first.__f_spare3 = other.__f_spare3;
    first.__f_spare4 = other.__f_spare4;
    first.__f_spare5 = other.__f_spare5;
    first.__isset = other.__isset;
}

void copyThriftFuseFileInfo(thrift_fuse_file_info& first, const thrift_fuse_file_info& other) {
    first.flags = other.flags;
    first.fh_old = other.fh_old;
    first.writepage = other.writepage;
    first.direct_io = other.direct_io;
    first.keep_cache = other.keep_cache;
    first.flush = other.flush;
    first.nonseekable = other.nonseekable;
    first.flock_release = other.flock_release;
    first.padding = other.padding;
    first.fh = other.fh;
    first.lock_owner = other.lock_owner;
    first.__isset = other.__isset;
}

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

    copyThriftStat(stbuf, reply.tstbuf);
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

    buf.assign(reply.tbuf);
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

int ThriftNfsRpc_Client::xmp_readdir(std::string tpath, int64_t offset, thrift_fuse_file_info &tfi, thrift_readdir_reply &reply) {
    transport->open();
    client.xmp_readdir(reply, tpath, offset, tfi);
    transport->close();
    return reply.retVal;
}

int ThriftNfsRpc_Client::xmp_statfs(string path, thrift_statvfs &stbuf) {
    thrift_statfs_reply reply;
    transport->open();
    client.xmp_statfs(reply, path, stbuf);
    transport->close();

    copyThriftStatvfs(stbuf, reply.tstbuf);
    return reply.retVal;
}

int ThriftNfsRpc_Client::xmp_open(string path, thrift_fuse_file_info &fi) {

    thrift_open_reply open_reply;

    try {

        transport->open();
        client.xmp_open(open_reply, path, fi);
        transport->close();

        copyThriftFuseFileInfo(fi, open_reply.tfi);

    } catch (TException &tx) {
        cout << "ERROR: " << tx.what() << endl;
    }
    return open_reply.retVal;
}

int ThriftNfsRpc_Client::xmp_access(std::string &tpath, int mask){
    int retVal = -1;
    transport->open();
    retVal = client.xmp_access(tpath, mask);
    transport->close();
    return retVal;
}

int ThriftNfsRpc_Client::xmp_mknod(std::string &tpath, int mode, int64_t rdev){
    int retVal = -1;
    transport->open();
    retVal = client.xmp_mknod(tpath, mode, rdev);
    transport->close();
    return retVal;
}

void ThriftNfsRpc_Client::xmp_readlink(thrift_readlink_reply& _return, std::string& tpath, std::string& tbuf, int64_t size){

    transport->open();
    client.xmp_readlink(_return, tpath, tbuf, size);
    transport->close();
}

int ThriftNfsRpc_Client::xmp_symlink(std::string& tfrom, std::string& tto){
    int retVal = -1;
    transport->open();
    retVal = client.xmp_symlink(tfrom, tto);
    transport->close();
    return retVal;
}

int ThriftNfsRpc_Client::xmp_link(std::string& tfrom, std::string& tto){
    int retVal = -1;
    transport->open();
    retVal = client.xmp_link(tfrom, tto);
    transport->close();
    return retVal;
}

int ThriftNfsRpc_Client::xmp_chmod(std::string& tpath, int mode){
    int retVal = -1;
    transport->open();
    retVal = client.xmp_chmod(tpath, mode);
    transport->close();
    return retVal;
}

int ThriftNfsRpc_Client::xmp_chown(std::string& tpath, int uid, int gid){
    int retVal = -1;
    transport->open();
    retVal = client.xmp_chown(tpath, uid, gid);
    transport->close();
    return retVal;
}

int ThriftNfsRpc_Client::xmp_truncate(std::string& tpath, int64_t size){
    int retVal = -1;
    transport->open();
    retVal = client.xmp_truncate(tpath, size);
    transport->close();
    return retVal;
}

int ThriftNfsRpc_Client::xmp_release(std::string& tpath, thrift_fuse_file_info& tfi, int32_t num){
    int retVal = -1;

    transport->open();
    retVal = client.xmp_release(tpath, tfi, num);
    transport->close();
    return retVal;
}

int ThriftNfsRpc_Client::xmp_fsync(std::string& tpath, int isdatasync, thrift_fuse_file_info& tfi, int32_t num){

    thrift_fsync_reply reply;
    transport->open();
    client.xmp_fsync(reply, tpath, isdatasync, tfi, num);
    transport->close();

    copyThriftFuseFileInfo(tfi, reply.tfi);
    return reply.retVal;
}



//int main(int argc, char **argv) {
//    cout << "Hello World - Thrift Client" << endl;
//    char * hostName = strdup("localhost");
//    ThriftNfsRpc_Client rpcClient(hostName, 9090);
//    rpcClient.xmp_unlink("asd");
//}