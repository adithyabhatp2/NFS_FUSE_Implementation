// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "gen-cpp/NfsRpc.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <thrift/server/TThreadPoolServer.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PlatformThreadFactory.h>


using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

#include "RPCGateway.h"
#include "WriteCache.h"

#include <iostream>

using namespace std;

WriteCache writeCache;
string pathPrefix;

class NfsRpcHandler : virtual public NfsRpcIf {
public:

    RPCGateway rpcGateway;

    NfsRpcHandler() {
        // Your initialization goes here
    }

    int32_t xmp_create(const std::string &tpath, const int32_t mode, const thrift_fuse_file_info &tfi) {
        // Your implementation goes here
        // printf("xmp_create: %s\n", (pathPrefix + tpath).c_str());
        thrift_fuse_file_info tfi2(tfi);
        return rpcGateway.xmp_create((pathPrefix + tpath), mode, tfi2);
    }

    int32_t xmp_unlink(const std::string &tpath) {
        // Your implementation goes here
        // printf("xmp_unlink: %s\n", (pathPrefix + tpath).c_str());
        return rpcGateway.xmp_unlink(pathPrefix + tpath);
    }

    void xmp_getattr(thrift_getattr_reply &_return, const std::string &tpath, const thrift_stat &stbuf) {
        // Your implementation goes here
        // printf("xmp_getattr: %s\n", (pathPrefix + tpath).c_str());
        thrift_stat tstbuf(stbuf);
        int retVal = rpcGateway.xmp_getattr(pathPrefix + tpath, tstbuf);
        _return.tstbuf=tstbuf;
        _return.retVal=retVal;
    }

    int32_t xmp_setattr(const std::string &tpath, const thrift_stat &stbuf) {
        // Your implementation goes here
        // printf("xmp_setattr - should not happen: %s\n", (pathPrefix+tpath).c_str());
        return 0;
    }

    void xmp_read(thrift_read_reply &_return, const std::string &tpath, const std::string &tbuf, const int64_t size,
                  const int64_t offset, const thrift_fuse_file_info &tfi) {
        // Your implementation goes here
        // printf("xmp_read: %s\n", (pathPrefix + tpath).c_str());
        string tbuf2;
        thrift_fuse_file_info tfi2(tfi);
        int retVal = rpcGateway.xmp_read(pathPrefix + tpath, tbuf2, size, offset, tfi2);
        _return.retVal=retVal;
        _return.tbuf=tbuf2;
    }

    int32_t xmp_write(const std::string &tpath, const std::string &tbuf, const int64_t size, const int64_t offset,
                      const thrift_fuse_file_info &tfi) {
        // Your implementation goes here
        // printf("xmp_write: %s\n", (pathPrefix + tpath).c_str());
        string tbuf2(tbuf);
        thrift_fuse_file_info tfi2(tfi);
//        int retVal = rpcGateway.xmp_write(pathPrefix + tpath, tbuf2, size, offset, tfi2);

        WriteCacheEntry cacheEntry(-1, pathPrefix+tpath, tbuf2, size, offset, tfi2);
        writeCache.insert(cacheEntry);

        int retVal = size;
        return retVal;
    }

    int32_t xmp_rename(const std::string &tfrom, const std::string &tto) {
        // Your implementation goes here
        // printf("xmp_rename: %s\t%s\n", (pathPrefix+tfrom).c_str(), (pathPrefix+tto).c_str());
        return rpcGateway.xmp_rename(pathPrefix + tfrom, pathPrefix + tto);
    }

    int32_t xmp_mkdir(const std::string &tpath, const int32_t mode) {
        // Your implementation goes here
        // printf("xmp_mkdir: %s\n", (pathPrefix + tpath).c_str());
        return rpcGateway.xmp_mkdir(pathPrefix + tpath, mode);
    }

    int32_t xmp_rmdir(const std::string &tpath) {
        // Your implementation goes here
        // printf("xmp_rmdir: %s\n", (pathPrefix + tpath).c_str());
        return rpcGateway.xmp_rmdir(pathPrefix + tpath);
    }

    void xmp_readdir(thrift_readdir_reply& _return, const std::string& tpath, const int64_t offset, const thrift_fuse_file_info& tfi) {
        // Your implementation goes here
        // printf("xmp_readdir: %s\n", (pathPrefix+tpath).c_str());
        thrift_fuse_file_info tfi2(tfi);
        vector<thrift_dir_entry> entries;
        _return.retVal = rpcGateway.xmp_readdir(pathPrefix + tpath, offset, tfi2, entries);
        _return.dir_entries = entries;
    }

    void xmp_statfs(thrift_statfs_reply &_return, const std::string &tpath, const thrift_statvfs &tstbuf) {
        // Your implementation goes here
        // printf("xmp_statfs: %s\n", (pathPrefix + tpath).c_str());
        thrift_statvfs tstbuf2(tstbuf);
        int retVal = rpcGateway.xmp_statfs(pathPrefix + tpath, tstbuf2);
        _return.retVal = retVal;
        _return.tstbuf=tstbuf2;
    }

    void xmp_open(thrift_open_reply &_return, const std::string &tpath, const thrift_fuse_file_info &tfi) {
        // Your implementation goes here
        // printf("xmp_open: %s\n", (pathPrefix + tpath).c_str());
        thrift_fuse_file_info tfi2(tfi);
        int retVal = rpcGateway.xmp_open(pathPrefix + tpath, tfi2);
        _return.tfi=tfi2;
        _return.retVal = retVal;
    }

    int32_t xmp_access(const std::string &tpath, const int32_t mask) {
        // Your implementation goes here
        // printf("xmp_access: %s\n", (pathPrefix + tpath).c_str());
        return rpcGateway.xmp_access(pathPrefix + tpath, mask);
    }

    int32_t xmp_mknod(const std::string &tpath, const int32_t mode, const int64_t rdev) {
        // Your implementation goes here
        // printf("xmp_mknod :%s\n", (pathPrefix + tpath).c_str());
        return rpcGateway.xmp_mknod(pathPrefix + tpath, mode, rdev);
    }

    void xmp_readlink(thrift_readlink_reply& _return, const std::string& tpath, const std::string& tbuf, const int64_t size) {
        // Your implementation goes here
        // printf("xmp_readlink: %s\n", (pathPrefix+tpath).c_str());
        string tbuf2(tbuf);
        int retVal = rpcGateway.xmp_readlink(pathPrefix+tpath, tbuf2, size);
        _return.tbuf=tbuf2;
        _return.retVal = retVal;
    }

    int32_t xmp_symlink(const std::string& tfrom, const std::string& tto) {
        // Your implementation goes here
        // printf("xmp_symlink: %s\t%s\n", (pathPrefix+tfrom).c_str(), (pathPrefix+tto).c_str());
        return rpcGateway.xmp_symlink(pathPrefix+tfrom, pathPrefix+tto);
    }

    int32_t xmp_link(const std::string& tfrom, const std::string& tto) {
        // Your implementation goes here
        // printf("xmp_link: %s\t%s\n", (pathPrefix+tfrom).c_str(), (pathPrefix+tto).c_str());
        return rpcGateway.xmp_link(pathPrefix+tfrom, pathPrefix+tto);
    }

    int32_t xmp_chmod(const std::string& tpath, const int32_t mode) {
        // Your implementation goes here
        // printf("xmp_chmod: %s\n", (pathPrefix+tpath).c_str());
        return rpcGateway.xmp_chmod(pathPrefix+tpath, mode);
    }

    int32_t xmp_chown(const std::string& tpath, const int32_t uid, const int32_t gid) {
        // Your implementation goes here
        // printf("xmp_chown: %s\n", (pathPrefix+tpath).c_str());
        return rpcGateway.xmp_chown(pathPrefix+tpath, uid, gid);
    }

    int32_t xmp_truncate(const std::string& tpath, const int64_t size) {
        // Your implementation goes here
        // printf("xmp_truncate: %s\n", (pathPrefix+tpath).c_str());
        return rpcGateway.xmp_truncate(pathPrefix+tpath, size);
    }

    int32_t xmp_release(const std::string& tpath, const thrift_fuse_file_info& tfi, const int32_t num) {
        // Your implementation goes here
        // printf("xmp_release: %s\n", (pathPrefix+tpath).c_str());
        thrift_fuse_file_info tfi2(tfi);
        return rpcGateway.xmp_release(pathPrefix+tpath, tfi2); // does nothing

//        return writeCache.writeNumForPath(pathPrefix+tpath, num); // flushes
    }

    void xmp_fsync(thrift_fsync_reply& _return, const std::string& tpath, const int32_t isdatasync, const thrift_fuse_file_info& tfi, const int32_t num) {
        // Your implementation goes here
        // printf("xmp_fsync: %s\n", (pathPrefix+tpath).c_str());
        thrift_fuse_file_info tfi2(tfi);

//        _return.retVal = rpcGateway.xmp_fsync(tpath, isdatasync, tfi2);
//        _return.isdatasync = isdatasync;
//        _return.__set_tfi(tfi2);



        writeCache.rpcGateway = rpcGateway;
//        int retVal = writeCache.writeNumForPath(pathPrefix+tpath, num);
        writeCache.writeAll();
        _return.isdatasync = isdatasync;
        _return.__set_tfi(tfi2);
        _return.retVal = 100;

    }
    
};

int main(int argc, char **argv) {

    int port = 9090;

    shared_ptr<NfsRpcHandler> handler(new NfsRpcHandler());
    shared_ptr<TProcessor> processor(new NfsRpcProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    // START SIMPLE SERVER
    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    // END SIMPLE SERVER


    // START THREADED SERVER
    const int workerCount = 16;

    shared_ptr<concurrency::PosixThreadFactory> threadFactory(new concurrency::PosixThreadFactory());
    shared_ptr<concurrency::ThreadManager> threadManager = concurrency::ThreadManager::newSimpleThreadManager(workerCount);
    threadManager->threadFactory(threadFactory);
    threadManager->start();

    // This server allows "workerCount" connection at a time, and reuses threads
    // adbhat : verified working - sleep in mkdir, 2 clients on 2 different mount points
    TThreadPoolServer server2(processor, serverTransport, transportFactory, protocolFactory, threadManager);
    // END THREADED SERVER




    if(argc < 2) {
        cout << "Not enough arguments - need atleast 2, got " << argc << endl;
        cout << "Usage : <executable> <startup dir>";
        exit(0);
    }

    pathPrefix=string(argv[1]);
    if(argv[1][pathPrefix.length()-1] == '/') {
        pathPrefix = pathPrefix.erase(pathPrefix.length()-1);
    }

    cout << "Starting Thrift Server" << endl;
    cout << "host location : "<< pathPrefix << endl;

//    RPCGateway rpcGateway;
//    rpcGateway.xmp_mkdir(pathPrefix + "dir1", S_IRWXU | S_IRWXG | S_IRWXO);
//    rpcGateway.xmp_rename(pathPrefix+"a.txt", pathPrefix+"b.txt");
//    rpcGateway.xmp_mkdir(pathPrefix + "dir2", S_IRWXU | S_IRWXG | S_IRWXO);

//    thrift_fuse_file_info tfi;
//    vector<thrift_dir_entry> entries;
//    int retVal = rpcGateway.xmp_readdir(pathPrefix, 0, tfi, entries);

    server2.serve();
    return 0;
}

