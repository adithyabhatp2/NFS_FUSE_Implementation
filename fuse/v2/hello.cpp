/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.

  gcc -Wall hello.c `pkg-config fuse --cflags --libs` -o hello

  echo `pkg-config fuse --cflags --libs`
  -D_FILE_OFFSET_BITS=64 -I/u/a/d/adbhat/Software/include/fuse -pthread -L/u/a/d/adbhat/Software/lib -lfuse

*/

#define FUSE_USE_VERSION 26
#define DEBUGLEVEL 1

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <iostream>





static const char *hello_str = "Hello World!\n";
static const char *hello_path = "/hello";

static int hello_getattr(const char *path, struct stat *stbuf) {
    int res = 0;

    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    } else if (strcmp(path, hello_path) == 0) {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(hello_str);
    } else
        res = -ENOENT;

    return res;
}

static int hello_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                         off_t offset, struct fuse_file_info *fi) {
    (void) offset;
    (void) fi;

    if (strcmp(path, "/") != 0)
        return -ENOENT;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    filler(buf, hello_path + 1, NULL, 0);

    return 0;
}

static int hello_open(const char *path, struct fuse_file_info *fi) {
    if (strcmp(path, hello_path) != 0)
        return -ENOENT;

    if ((fi->flags & 3) != O_RDONLY)
        return -EACCES;

    return 0;
}

static int hello_read(const char *path, char *buf, size_t size, off_t offset,
                      struct fuse_file_info *fi) {
    size_t len;
    (void) fi;
    if (strcmp(path, hello_path) != 0)
        return -ENOENT;

    len = strlen(hello_str);
    if (offset < len) {
        if (offset + size > len)
            size = len - offset;
        memcpy(buf, hello_str + offset, size);
    } else
        size = 0;

    return size;
}

static struct hello_operations : fuse_operations {
    hello_operations() {
        getattr = hello_getattr;
        readdir = hello_readdir;
        open = hello_open;
        read = hello_read;
    }
}hello_oper;

int main(int argc, char *argv[]) {

    if (argc < 9) {
        printf("Insufficient parameters!\n");
        clientUsage();
    }

    unsigned long int serverPort = UINT_MAX;
    unsigned long numPkts = 10;
    unsigned long msgLen = 10;

    char *hostName;
    int ch;

    // Read input params from cmd line
    while ((ch = getopt(argc, argv, "s:p:n:l:")) != -1) {
        switch (ch) {
            case 's':
                hostName = strdup(optarg);
                break;
            case 'p':
                serverPort = strtoul(optarg, NULL, 10);
                if (serverPort <= 1024 || serverPort > 65536) {
                    printf("Invalid Port\n");
                    clientUsage();
                }
                break;
            case 'n':
                numPkts = strtoul(optarg, NULL, 10);
                if (numPkts == 0 && errno == EINVAL) {
                    clientUsage();
                }
                break;
            case 'l':
                msgLen = strtoul(optarg, NULL, 10);
                if (msgLen == 0 && errno == EINVAL) {
                    clientUsage();
                }
                break;
            case '?':
            default:
                clientUsage();
                return 0;
        }
    }


//    communicatewithServer(hostName, serverPort, numPkts, msgLen);


//    char exitCh = 0;
//    cin >> exitCh;

    RPCClient client;

    return fuse_main(argc, argv, &hello_oper, NULL);
}
