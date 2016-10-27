//
// Created by adbhat on 10/26/16.
//

#include "WriteCache.h"

WriteCache::WriteCache(RPCGateway rpg) {
    this->rpcGateway = rpg;
}

int WriteCache::writeAll() {

    for (std::vector<WriteCacheEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
        int bytesWritten = rpcGateway.xmp_write(it->path, it->tbuf, it->size, it->offset, it->tfi);
        rpcGateway.xmp_fsync(it->path, 1, it->tfi, 1);
    }

    this->entries.clear();

    return 1;

}

void WriteCache::insert(WriteCacheEntry entry) {
    entries.push_back(entry);
}

int WriteCache::writeNumForPath(const char * path, int num) {

    int numWritten = 0;

    for (std::vector<WriteCacheEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
        if(strcmp(it->path,path)==0) {
            int bytesWritten = rpcGateway.xmp_write(it->path, it->tbuf, it->size, it->offset, it->tfi);
            numWritten++;
            it = entries.erase(it);
        }
    }

    return numWritten;
}

