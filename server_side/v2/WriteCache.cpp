//
// Created by adbhat on 10/26/16.
//

#include "WriteCache.h"

#define debuglevel 2

#include <iostream>
using namespace std;

int WriteCache::writeAll() {

    for (std::vector<WriteCacheEntry>::iterator it = entries.begin(); it != entries.end(); ++it) {
        int bytesWritten = rpcGateway.xmp_write(it->path, it->tbuf, it->size, it->offset, it->tfi);
    }

    this->entries.clear();

    return 1;

}

void WriteCache::insert(WriteCacheEntry entry) {
    entries.push_back(entry);
}

int WriteCache::writeNumForPath(std::string path, int num) {

    int numWritten = 0;

    if(debuglevel <= 1) {
        cout << "In write num for path: " << num << endl;
    }

    for (std::vector<WriteCacheEntry>::iterator it = entries.begin(); it != entries.end(); ) {
        if(debuglevel <= 1) {
            cout << "WNFP: going to compare strings " << endl;
        }
        if(it->path.compare(path)==0) {
            if(debuglevel <= 1) {
                cout << "WNFP: going to write " << endl;
            }
            int bytesWritten = rpcGateway.xmp_write(it->path, it->tbuf, it->size, it->offset, it->tfi);
            numWritten++;
            if(debuglevel <= 1) {
                cout << "WNFP: going to erase " << endl;
            }
            it = entries.erase(it);
        } else {
            ++it;
        }
    }

    return numWritten;

}