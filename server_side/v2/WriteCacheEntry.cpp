//
// Created by adbhat on 10/26/16.
//

#include "WriteCacheEntry.h"

#include <iostream>
using namespace std;

WriteCacheEntry::WriteCacheEntry(int fd, std::string path, std::string tbuf, int64_t size, int64_t offset,
                                 thrift_fuse_file_info &tfi) {
    this->fd = fd;
    this->path = string(path);
    this->tbuf = string(tbuf);
    this->size = size;
    this->offset = offset;
    this->tfi = tfi;
}