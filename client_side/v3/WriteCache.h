//
// Created by adbhat on 10/26/16.
//

#ifndef NFSSERVER_V2_WRITECACHE_H
#define NFSSERVER_V2_WRITECACHE_H


#include "WriteCacheEntry.h"
#include "RPCGateway.h"

class WriteCache {
public:
    WriteCache(RPCGateway rpcg);
    RPCGateway rpcGateway;
    std::vector<WriteCacheEntry> entries;
    int writeAll();
    void insert(WriteCacheEntry entry);
    int writeNumForPath(const char * path, int num);
};


#endif //NFSSERVER_V2_WRITECACHE_H
