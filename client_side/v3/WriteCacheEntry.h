//
// Created by adbhat on 10/26/16.
//

#ifndef NFSSERVER_V2_WRITECACHEENTRY_H
#define NFSSERVER_V2_WRITECACHEENTRY_H

#include <string>
#include <NfsRpc_types.h>

class WriteCacheEntry {

public:
//    WriteCacheEntry();

    WriteCacheEntry(int fd, const char * path, const char * tbuf, int64_t size, int64_t offset, struct fuse_file_info *tfi);

    int fd;
    char * path;
    char * tbuf;
    int64_t size;
    int64_t offset;
    struct fuse_file_info *tfi;
};


#endif //NFSSERVER_V2_WRITECACHEENTRY_H
