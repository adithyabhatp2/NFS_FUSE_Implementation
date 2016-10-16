/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>
  Copyright (C) 2011       Sebastian Pipping <sebastian@pipping.org>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.

  gcc -Wall fusexmp.c `pkg-config fuse --cflags --libs` -o fusexmp
*/

#include "NFSClient.h"

#include<iostream>
using namespace std;

//RPCGateway rpcGateway;

int NFSClient::xmp_open(const char *path, struct fuse_file_info *fi)
{
    int res;

     // res = rpcGateway.xmp_open(path, fi);
    if (res == -1)
        return -errno;

    close(res);
    return 0;
}

int NFSClient::xmp_access(const char *path, int mask)
{
	int res;

	 // res = rpcGateway.xmp_access(path, mask);
	if (res == -1)
		return -errno;

	return 0;
}


// Start necessary as per NFS protocol


/// The system call mknod() creates a file system node (file..)
/// https://linux.die.net/man/2/mknod
/// Create
///
/// \param path
/// \param mode - unsigned int (32?)
/// \param rdev - unsigned long int
/// \return
int NFSClient::xmp_mknod(const char *path, mode_t mode, dev_t rdev)
{
    int res;

     // res = rpcGateway.xmp_mknod(path, mode, rdev);
    if (res == -1)
        return -errno;

    return 0;
}

int NFSClient::xmp_remove(const char *path)
{
    int res;

    // res = rpcGateway.xmp_remove(path);
    if (res == -1)
        return -errno;

    return 0;
}

int NFSClient::xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;

    // res = rpcGateway.xmp_getattr(path, stbuf);
    if (res == -1)
        return -errno;

    return 0;
}

int NFSClient::xmp_setattr(const char *path, struct stat *stbuf)
{
    int res;

    // res = rpcGateway.xmp_setattr(path, stbuf);
    if (res == -1)
        return -errno;

    return 0;
}


int NFSClient::xmp_read(const char *path, char *buf, size_t size, off_t offset,
                    struct fuse_file_info *fi)
{
    int res;

    // res = rpcGateway.xmp_read(path, buf, size, offset, fi);
    if (res == -1)
        res = -errno;

    return res;
}


int NFSClient::xmp_write(const char *path, const char *buf, size_t size,
                     off_t offset, struct fuse_file_info *fi)
{
//    int fd;
    int res;

//    (void) fi;
//    fd = open(path, O_WRONLY);
//    if (fd == -1)
//        return -errno;

//    res = pwrite(fd, buf, size, offset);
    // res = rpcGateway.xmp_write(path, buf, size, offset, fi);
    if (res == -1)
        res = -errno;

//    close(fd);
    return res;
}

int NFSClient::xmp_rename(const char *from, const char *to)
{
    int res;

    // res = rpcGateway.xmp_rename(from, to);
    if (res == -1)
        return -errno;

    return 0;
}


int NFSClient::xmp_mkdir(const char *path, mode_t mode)
{
	int res;

	// res = rpcGateway.xmp_mkdir(path, mode);
	if (res == -1)
		return -errno;

	return 0;
}

int NFSClient::xmp_rmdir(const char *path)
{
	int res;

	// res = rpcGateway.xmp_mkdir(path);
	if (res == -1)
		return -errno;

	return 0;
}


//int NFSClient::xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
//                       off_t offset, struct fuse_file_info *fi)
//{
//    DIR *dp;
//    struct dirent *de;
//
//    (void) offset;
//    (void) fi;
//
//    dp = opendir(path);
//    if (dp == NULL)
//        return -errno;
//
//    while ((de = readdir(dp)) != NULL) {
//        struct stat st;
//        memset(&st, 0, sizeof(st));
//        st.st_ino = de->d_ino;
//        st.st_mode = de->d_type << 12;
//        if (filler(buf, de->d_name, &st, 0))
//            break;
//    }
//
//    closedir(dp);
//    return 0;
//}


int NFSClient::xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                           off_t offset, struct fuse_file_info *fi)
{
    int res;
    // res = rpcGateway.xmp_readdir(path, buf, filler, offset, fi);
    return res;
}


int NFSClient::xmp_statfs(const char *path, struct statvfs *stbuf)
{
    int res;

    // res = rpcGateway.xmp_statfs(path, stbuf);
    if (res == -1)
        return -errno;

    return 0;
}


// Above are necessary as per NFS protocol

/*
int xmp_chmod(const char *path, mode_t mode)
{
	int res;

	res = chmod(path, mode);
	if (res == -1)
		return -errno;

	return 0;
}

int xmp_chown(const char *path, uid_t uid, gid_t gid)
{
	int res;

	res = lchown(path, uid, gid);
	if (res == -1)
		return -errno;

	return 0;
}

int xmp_truncate(const char *path, off_t size)
{
	int res;

	res = truncate(path, size);
	if (res == -1)
		return -errno;

	return 0;
}

int xmp_release(const char *path, struct fuse_file_info *fi)
{
    // Just a stub. This method is optional and can safely be left unimplemented.

	(void) path;
	(void) fi;
	return 0;
}


int xmp_fsync(const char *path, int isdatasync,
		     struct fuse_file_info *fi)
{
    // Just a stub. This method is optional and can safely be left unimplemented.

	(void) path;
	(void) isdatasync;
	(void) fi;
	return 0;
}
*/


int main(int argc, char *argv[])
{
    cout << "NFS Client.cpp - main "<< endl;
    NFSClient nfsClient;

    return 0;
}
