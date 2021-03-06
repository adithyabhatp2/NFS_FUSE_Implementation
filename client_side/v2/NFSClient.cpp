/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>
  Copyright (C) 2011       Sebastian Pipping <sebastian@pipping.org>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.

  gcc -Wall fusexmp.c `pkg-config fuse --cflags --libs` -o fusexmp
*/

#define FUSE_USE_VERSION 26

#ifdef HAVE_CONFIG_H
//#include <config.h>
#endif

#ifdef linux
/* For pread()/pwrite()/utimensat() */
#define _XOPEN_SOURCE 700
#endif

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#ifdef HAVE_SETXATTR
#include <sys/xattr.h>
#endif

#include "RPCGateway.h"

#include "iostream"
using namespace std;

// init from a config file later
static RPCGateway rpcGateway("instance-2.c.quick-elixir-137423.internal", 9080); // v1 server


static void printStat(struct stat* stbuf) {
    cout << "Printing the stat" << endl;
    cout << " stbuf->__glibc_reserved[0] " <<  " : "  << stbuf->__glibc_reserved[0]  << endl;
    cout << " stbuf->__glibc_reserved[1] " <<  " : "  << stbuf->__glibc_reserved[1]  << endl;
    cout << " stbuf->__glibc_reserved[2] " <<  " : "  << stbuf->__glibc_reserved[2]  << endl;
    cout << " stbuf->__pad0 " <<  " : "  << stbuf->__pad0  << endl;
    cout << " stbuf->st_blocks " <<  " : "  << stbuf->st_blocks  << endl;
    cout << " stbuf->st_blksize " <<  " : "  << stbuf->st_blksize  << endl;
    cout << " stbuf->st_dev " <<  " : "  << stbuf->st_dev  << endl;
    cout << " stbuf->st_gid " <<  " : "  << stbuf->st_gid  << endl;
    cout << " stbuf->st_ino " <<  " : "  << stbuf->st_ino  << endl;
    cout << " stbuf->st_mode " <<  " : "  << stbuf->st_mode  << endl;
    cout << " stbuf->st_nlink " <<  " : "  << stbuf->st_nlink  << endl;
    cout << " stbuf->st_rdev " <<  " : "  << stbuf->st_rdev  << endl;
    cout << " stbuf->st_size " <<  " : "  << stbuf->st_size  << endl;
    cout << " stbuf->st_uid " <<  " : "  << stbuf->st_uid  << endl;
    cout << " stbuf->st_atim.tv_nsec " <<  " : "  << stbuf->st_atim.tv_nsec  << endl;
    cout << " stbuf->st_ctim.tv_nsec " <<  " : "  << stbuf->st_ctim.tv_nsec  << endl;
    cout << " stbuf->st_mtim.tv_nsec " <<  " : "  << stbuf->st_mtim.tv_nsec  << endl;
    cout << " stbuf->st_atim.tv_sec " <<  " : "  << stbuf->st_atim.tv_sec  << endl;
    cout << " stbuf->st_ctim.tv_sec " <<  " : "  << stbuf->st_ctim.tv_sec  << endl;
    cout << " stbuf->st_mtim.tv_sec " <<  " : "  << stbuf->st_mtim.tv_sec  << endl;
}


static int xmp_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
    int fd;

    fd = rpcGateway.xmp_create(path, mode, fi);

    if (fd < 0)
        return fd;

    fi->fh = fd;
    return 0;
}

static int xmp_unlink(const char *path)
{
    int res;

    res = rpcGateway.xmp_unlink(path);
    if (res < 0 )
        return res;

    return 0;
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;

    res = rpcGateway.xmp_getattr(path, stbuf);
    cout << "Getattr retVal = " << res << endl;
    if (res < 0)
        return res;

    return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
                    struct fuse_file_info *fi)
{
    int res;

    res = rpcGateway.xmp_read(path, buf, size, offset, fi);

//    if (res == -1)
//        res = -errno;

    return res;
}

static int xmp_write(const char *path, const char *buf, size_t size,
                     off_t offset, struct fuse_file_info *fi)
{
    int res;

//    cout << "write size: "<< size << " data: " << buf << endl;
    res = rpcGateway.xmp_write(path, buf, size, offset, fi);

//    if (res == -1)
//        res = -errno;

    return res;
}

static int xmp_rename(const char *from, const char *to)
{
    int res;

    res = rpcGateway.xmp_rename(from, to);

//    if (res == -1)
//        return -errno;

    return res;
}

static int xmp_mkdir(const char *path, mode_t mode)
{
    int res;

    res = rpcGateway.xmp_mkdir(path, mode);
//    if (res == -1)
//        return -errno;

    return res;
}

static int xmp_rmdir(const char *path)
{
    int res;

    res = rpcGateway.xmp_rmdir(path);
//    if (res == -1)
//        return -errno;

    return res;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                       off_t offset, struct fuse_file_info *fi)
{
    int res;

    res = rpcGateway.xmp_readdir(path, buf, filler, offset, fi);
//    if (res == -1)
//        return -errno;

    return res;
}


static int xmp_statfs(const char *path, struct statvfs *stbuf)
{
    int res;

    res = rpcGateway.xmp_statfs(path, stbuf);
//    if (res == -1)
//        return -errno;

    return res;
}

static int xmp_access(const char *path, int mask)
{
    int res;

    res = rpcGateway.xmp_access(path, mask);
//    if (res == -1)
//        return -errno;

    return res;
}

static int xmp_readlink(const char *path, char *buf, size_t size)
{
    int res;

    res = rpcGateway.xmp_readlink(path, buf, size - 1);
    if (res < 0)
        return res;

    buf[res] = '\0';
    return 0;
}


static int xmp_mknod(const char *path, mode_t mode, dev_t rdev)
{
    int res;
    res = rpcGateway.xmp_mknod(path, mode, rdev);
//    if (res == -1)
//        return -errno;

    return res;
}


static int xmp_symlink(const char *from, const char *to)
{
    int res;

    res = rpcGateway.xmp_symlink(from, to);
//    if (res == -1)
//        return -errno;

    return res;
}



static int xmp_link(const char *from, const char *to)
{
    int res;

    res = rpcGateway.xmp_link(from, to);
//    if (res == -1)
//        return -errno;

    return res;
}

static int xmp_chmod(const char *path, mode_t mode)
{
    int res;

    res = rpcGateway.xmp_chmod(path, mode);
//    if (res == -1)
//        return -errno;

    return res;
}

static int xmp_chown(const char *path, uid_t uid, gid_t gid)
{
    int res;

    res = rpcGateway.xmp_chown(path, uid, gid);
//    if (res == -1)
//        return -errno;

    return res;
}

static int xmp_truncate(const char *path, off_t size)
{
    int res;

    res = rpcGateway.xmp_truncate(path, size);
//    if (res == -1)
//        return -errno;

    return res;
}

#ifdef HAVE_UTIMENSAT
static int xmp_utimens(const char *path, const struct timespec ts[2])
{
	int res;

	/* don't use utime/utimes since they follow symlinks */
	res = utimensat(0, path, ts, AT_SYMLINK_NOFOLLOW);
	if (res == -1)
		return -errno;

	return 0;
}
#endif

static int xmp_open(const char *path, struct fuse_file_info *fi)
{
    int res;

    res = rpcGateway.xmp_open(path, fi);
    if (res < 0)
        return res;

    return 0;
}

static int xmp_release(const char *path, struct fuse_file_info *fi)
{
    int res;
    res = rpcGateway.xmp_release(path, fi);
//    if (res == -1)
//        return -errno;

    return res;
}

static int xmp_fsync(const char *path, int isdatasync, struct fuse_file_info *fi)
{
    int res;
    res = rpcGateway.xmp_fsync(path, isdatasync, fi);
//    if (res == -1)
//        return -errno;

    return res;
}

#ifdef HAVE_POSIX_FALLOCATE
static int xmp_fallocate(const char *path, int mode,
			off_t offset, off_t length, struct fuse_file_info *fi)
{
	int fd;
	int res;

	(void) fi;

	if (mode)
		return -EOPNOTSUPP;

	fd = open(path, O_WRONLY);
	if (fd == -1)
		return -errno;

	res = -posix_fallocate(fd, offset, length);

	close(fd);
	return res;
}
#endif

#ifdef HAVE_SETXATTR
/* xattr operations are optional and can safely be left unimplemented */
static int xmp_setxattr(const char *path, const char *name, const char *value,
			size_t size, int flags)
{
	int res = lsetxattr(path, name, value, size, flags);
	if (res == -1)
		return -errno;
	return 0;
}

static int xmp_getxattr(const char *path, const char *name, char *value,
			size_t size)
{
	int res = lgetxattr(path, name, value, size);
	if (res == -1)
		return -errno;
	return res;
}

static int xmp_listxattr(const char *path, char *list, size_t size)
{
	int res = llistxattr(path, list, size);
	if (res == -1)
		return -errno;
	return res;
}

static int xmp_removexattr(const char *path, const char *name)
{
	int res = lremovexattr(path, name);
	if (res == -1)
		return -errno;
	return 0;
}
#endif /* HAVE_SETXATTR */

static struct xmp_operations : fuse_operations {
    xmp_operations(){
        create = xmp_create;
        unlink = xmp_unlink;
        getattr	= xmp_getattr;
        access		= xmp_access;
        readlink	= xmp_readlink;
        readdir	= xmp_readdir;
        mknod		= xmp_mknod;
        mkdir		= xmp_mkdir;
        symlink	= xmp_symlink;
        unlink		= xmp_unlink;
        rmdir		= xmp_rmdir;
        rename		= xmp_rename;
        link		= xmp_link;
        chmod		= xmp_chmod;
        chown		= xmp_chown;
        truncate	= xmp_truncate;
#ifdef HAVE_UTIMENSAT
        utimens	= xmp_utimens;
#endif
        open		= xmp_open;
        read		= xmp_read;
        write		= xmp_write;
        statfs		= xmp_statfs;
        release	= xmp_release;
        fsync		= xmp_fsync;
#ifdef HAVE_POSIX_FALLOCATE
        fallocate	= xmp_fallocate;
#endif
#ifdef HAVE_SETXATTR
    setxattr	= xmp_setxattr;
	getxattr	= xmp_getxattr;
	listxattr	= xmp_listxattr;
	removexattr	= xmp_removexattr;
#endif
    }
}xmp_oper;

int main(int argc, char *argv[])
{
    cout << "NFS FUSE Client - main" << endl;
    umask(0);
    return fuse_main(argc, argv, &xmp_oper, NULL);
}
