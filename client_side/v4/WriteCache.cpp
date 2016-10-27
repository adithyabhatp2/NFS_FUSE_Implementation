//
// Created by adbhat on 10/26/16.
//

#include "WriteCache.h"

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

WriteCache::WriteCache(RPCGateway rpg) {
    this->rpcGateway = rpg;
}

int WriteCache::writeAll() {

    pthread_mutex_lock(&mutex1);

    for (std::vector<WriteCacheEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
        int bytesWritten = rpcGateway.xmp_write(it->path, it->tbuf, it->size, it->offset, it->tfi);
        rpcGateway.xmp_fsync(it->path, 1, it->tfi, 1);
    }

    this->entries.clear();

    pthread_mutex_unlock(&mutex1);

    return 1;

}

void WriteCache::insert(WriteCacheEntry entry) {
    entries.push_back(entry);
}

int WriteCache::writeNumForPath(const char * path, int num) {

    int numWritten = 0;

    pthread_mutex_lock(&mutex1);

    for (std::vector<WriteCacheEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
        if(strcmp(it->path,path)==0) {
            int bytesWritten = rpcGateway.xmp_write(it->path, it->tbuf, it->size, it->offset, it->tfi);
            numWritten++;
            it = entries.erase(it);
        }
    }

    pthread_mutex_unlock(&mutex1);

    return numWritten;
}

