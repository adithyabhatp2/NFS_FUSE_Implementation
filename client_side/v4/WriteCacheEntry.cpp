//
// Created by adbhat on 10/26/16.
//

#include "WriteCacheEntry.h"

#include <iostream>
#include <string.h>

using namespace std;

WriteCacheEntry::WriteCacheEntry(int fd, const char *path, const char *tbuf, int64_t size, int64_t offset,
                                 struct fuse_file_info *tfi) {
    this->fd = fd;
    this->path = strdup(path);
    this->tbuf = strdup(tbuf);
    this->size = size;
    this->offset = offset;
    this->tfi = tfi;
}