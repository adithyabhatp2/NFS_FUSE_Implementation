// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "gen-cpp/NfsRpc.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

#include <iostream>
using namespace std;

class NfsRpcHandler : virtual public NfsRpcIf {
 public:
  NfsRpcHandler() {
    // Your initialization goes here
  }

    int32_t xmp_create(const std::string& tpath, const int32_t mode, const thrift_fuse_file_info& tfi) {
      // Your implementation goes here
      printf("xmp_create\n");
      return 3;
    }

    int32_t xmp_unlink(const std::string& tpath) {
      // Your implementation goes here
      printf("xmp_unlink\n");
    }

    void xmp_getattr(thrift_getattr_reply& _return, const std::string& tpath, const thrift_stat& stbuf) {
      // Your implementation goes here
      _return.retVal = 0;
      printf("xmp_getattr\n");
    }

    int32_t xmp_setattr(const std::string& tpath, const thrift_stat& stbuf) {
      // Your implementation goes here
      printf("xmp_setattr\n");
    }

    void xmp_read(thrift_read_reply& _return, const std::string& tpath, const std::string& tbuf, const int64_t size, const int64_t offset, const thrift_fuse_file_info& tfi) {
      // Your implementation goes here
      printf("xmp_read\n");
    }

    int32_t xmp_write(const std::string& tpath, const std::string& tbuf, const int64_t size, const int64_t offset, const thrift_fuse_file_info& tfi) {
      // Your implementation goes here
      printf("xmp_write\n");
    }

    int32_t xmp_rename(const std::string& tfrom, const std::string& tto) {
      // Your implementation goes here
      printf("xmp_rename\n");
    }

    int32_t xmp_mkdir(const std::string& tpath, const int32_t mode) {
      // Your implementation goes here
      printf("xmp_mkdir\n");
    }

    int32_t xmp_rmdir(const std::string& tpath) {
      // Your implementation goes here
      printf("xmp_rmdir\n");
    }

    void xmp_statfs(thrift_statfs_reply& _return, const std::string& tpath, const thrift_statvfs& tstbuf) {
      // Your implementation goes here
      printf("xmp_statfs\n");
    }

    void xmp_open(thrift_open_reply& _return, const std::string& tpath, const thrift_fuse_file_info& tfi) {
      // Your implementation goes here
      printf("xmp_open\n");
    }

    int32_t xmp_access(const std::string& tpath, const int32_t mask) {
      // Your implementation goes here
      printf("xmp_access\n");
    }

    int32_t xmp_mknod(const std::string& tpath, const int32_t mode, const int64_t rdev) {
      // Your implementation goes here
      printf("xmp_mknod\n");
    }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<NfsRpcHandler> handler(new NfsRpcHandler());
  shared_ptr<TProcessor> processor(new NfsRpcProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);

    cout << "Starting Thrift Server" << endl;

  server.serve();
  return 0;
}

