//
// Created by adbhat on 10/17/16.
//

#ifndef RPCCLIENT_NFSRPC_CLIENT_H
#define RPCCLIENT_NFSRPC_CLIENT_H

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <vector>
#include "gen-cpp/NfsRpc.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

class ThriftNfsRpc_Client {
public:

    char * hostName;
    unsigned long int serverPort;

    boost::shared_ptr<TTransport> socket;
    boost::shared_ptr<TProtocol> protocol;
    boost::shared_ptr<TTransport> transport;

    NfsRpcClient client;

    ThriftNfsRpc_Client();
    ThriftNfsRpc_Client(char *, unsigned long);

    
    int xmp_unlink(std::string path);
    int xmp_getattr(std::string path, thrift_stat &stbuf);   

    int xmp_read(std::string path, std::string &buf, long int size, long int offset, thrift_fuse_file_info &fi);
    int xmp_write(std::string path, std::string &buf, long int size, long int offset, thrift_fuse_file_info &fi);
    int xmp_rename(std::string fromName, std::string to);
    int xmp_mkdir(std::string path, int mode);
    int xmp_rmdir(std::string path);
    int xmp_readdir(std::string tpath, int64_t offset, thrift_fuse_file_info& tfi, thrift_readdir_reply &reply);
    int xmp_statfs(std::string path, thrift_statvfs &stbuf);
    
    int xmp_open(std::string path, thrift_fuse_file_info &fi);
    int xmp_access(std::string &tpath, int mask);
    int xmp_mknod(std::string &tpath, int mode, int64_t rdev);
    void xmp_readlink(thrift_readlink_reply& _return, std::string& tpath, std::string& tbuf, int64_t size);
    int xmp_symlink(std::string& tfrom, std::string& tto);
    int xmp_link(std::string& tfrom, std::string& tto);
    int xmp_chmod(std::string& tpath, int mode);
    int xmp_chown(std::string& tpath, int uid, int gid);
    int xmp_truncate(std::string& tpath, int64_t size);
    int xmp_release(std::string& tpath, thrift_fuse_file_info& tfi, int num);
    int xmp_fsync(std::string& tpath, int isdatasync, thrift_fuse_file_info& tfi, int num);
    
    int xmp_create(std::string path, mode_t mode, thrift_fuse_file_info &fi);
    
    int xmp_setattr(std::string path, thrift_stat &stbuf);

};


#endif //RPCCLIENT_NFSRPC_CLIENT_H
