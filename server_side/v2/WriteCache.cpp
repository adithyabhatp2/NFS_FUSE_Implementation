//
// Created by adbhat on 10/26/16.
//

#include "WriteCache.h"


int WriteCache::writeAll() {

    for (std::vector<WriteCacheEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
        int bytesWritten = rpcGateway.xmp_write(it->path, it->tbuf, it->size, it->offset, it->tfi);
    }

    return 1;

}

void WriteCache::insert(WriteCacheEntry entry) {
    entries.push_back(entry);
}