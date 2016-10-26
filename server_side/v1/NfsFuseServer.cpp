//
// Created by adbhat on 10/24/16.
//

#include <vector>
#include <NfsRpc_types.h>
#include "NfsFuseServer.h"

#include "iostream"
using namespace std;


int NfsFuseServer::xmp_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
    int fd;

    fd = open(path, fi->flags, mode);
    if (fd == -1)
        return -errno;

    fi->fh = fd;
    return 0;
}

int NfsFuseServer::xmp_unlink(const char *path)
{
    int res;

    res = unlink(path);
    if (res == -1)
        return res;

    return 0;
}

int NfsFuseServer::xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;

    res = lstat(path, stbuf);
    if (res == -1)
        return res;

    return 0;
}

int NfsFuseServer::xmp_read(const char *path, char *buf, size_t size, off_t offset,
             struct fuse_file_info *fi)
{
    int fd;
    int res;

    (void) fi;
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return res;

    res = pread(fd, buf, size, offset);
    if (res == -1)
        res = -errno;

    close(fd);
    return res;
}

int NfsFuseServer::xmp_write(const char *path, const char *buf, size_t size,
              off_t offset, struct fuse_file_info *fi)
{
    int fd;
    int res;

    (void) fi;
    fd = open(path, O_WRONLY);
    if (fd == -1)
        return res;

    res = pwrite(fd, buf, size, offset);
    if (res == -1)
        res = -errno;

    close(fd);
    return res;
}

int NfsFuseServer::xmp_rename(const char *from, const char *to)
{
    int res;

    res = rename(from, to);
    if (res == -1)
        return res;

    return 0;
}

int NfsFuseServer::xmp_mkdir(const char *path, mode_t mode)
{
    int res;

    res = mkdir(path, mode);
    if (res == -1)
        return res;

    return 0;
}

int NfsFuseServer::xmp_rmdir(const char *path)
{
    int res;

    res = rmdir(path);
    if (res == -1)
        return res;

    return 0;
}

int NfsFuseServer::xmp_readdir(const char *path, off_t offset, struct fuse_file_info *fi, vector<thrift_dir_entry> &entries)
{
    DIR *dp;
    struct dirent *de;

    (void) offset;
    (void) fi;

    dp = opendir(path);
    if (dp == NULL)
        return -1; //errno

    while ((de = readdir(dp)) != NULL) {
//        struct stat st;
//        memset(&st, 0, sizeof(st));
        thrift_dir_entry entry;
        entry.__set_d_ino(de->d_ino);
        entry.__set_d_name(de->d_name);
        entry.__set_d_type(de->d_type);
        entries.push_back(entry);
    }

    closedir(dp);
    return 0;
}

int NfsFuseServer::xmp_statfs(const char *path, struct statvfs *stbuf)
{
    int res;

    res = statvfs(path, stbuf);
    if (res == -1)
        return res;

    return 0;
}



int NfsFuseServer::xmp_access(const char *path, int mask)
{
    int res;

    res = access(path, mask);
    if (res == -1)
        return res;

    return 0;
}

int NfsFuseServer::xmp_readlink(const char *path, char *buf, size_t size)
{
    int res;

    res = readlink(path, buf, size - 1);
    if (res == -1)
        return res;

    buf[res] = '\0';
    return 0;
}

int NfsFuseServer::xmp_mknod(const char *path, mode_t mode, dev_t rdev)
{
    int res;

    /* On Linux this could just be 'mknod(path, mode, rdev)' but this
       is more portable */
    if (S_ISREG(mode)) {
        res = open(path, O_CREAT | O_EXCL | O_WRONLY, mode);
        if (res >= 0)
            res = close(res);
    } else if (S_ISFIFO(mode))
        res = mkfifo(path, mode);
    else
        res = mknod(path, mode, rdev);
    if (res == -1)
        return res;

    return 0;
}

int NfsFuseServer::xmp_symlink(const char *from, const char *to)
{
    int res;

    res = symlink(from, to);
    if (res == -1)
        return res;

    return 0;
}

int NfsFuseServer::xmp_link(const char *from, const char *to)
{
    int res;

    res = link(from, to);
    if (res == -1)
        return res;

    return 0;
}

int NfsFuseServer::xmp_chmod(const char *path, mode_t mode)
{
    int res;

    res = chmod(path, mode);
    if (res == -1)
        return res;

    return 0;
}

int NfsFuseServer::xmp_chown(const char *path, uid_t uid, gid_t gid)
{
    int res;

    res = lchown(path, uid, gid);
    if (res == -1)
        return res;

    return 0;
}

int NfsFuseServer::xmp_truncate(const char *path, off_t size)
{
    int res;

    res = truncate(path, size);
    if (res == -1)
        return res;

    return 0;
}

#ifdef HAVE_UTIMENSAT
int NfsFuseServer::xmp_utimens(const char *path, const struct timespec ts[2])
{
	int res;

	/* don't use utime/utimes since they follow symlinks */
	res = utimensat(0, path, ts, AT_SYMLINK_NOFOLLOW);
	if (res == -1)
		return res;

	return 0;
}
#endif

int NfsFuseServer::xmp_open(const char *path, struct fuse_file_info *fi)
{
    int res;

    res = open(path, fi->flags);
    if (res == -1)
        return res;

    close(res);
    return 0;
}



int NfsFuseServer::xmp_release(const char *path, struct fuse_file_info *fi)
{
    /* Just a stub.	 This method is optional and can safely be left
       unimplemented */

    (void) path;
    (void) fi;
    return 0;
}

int NfsFuseServer::xmp_fsync(const char *path, int isdatasync,
                     struct fuse_file_info *fi)
{
    /* Just a stub.	 This method is optional and can safely be left
       unimplemented */

    (void) path;
    (void) isdatasync;
    (void) fi;
    return 0;
}

//int main(int argc, char *argv[])
//{
//    cout << "NFS Server.cpp - main "<< endl;
//    NfsFuseServer server;
//    server.xmp_unlink("/u/a/d/adbhat/private/gitRepository/NFS_FUSE_Implementation/server_side/v1/temp.txt");
//
//    string pathPrefix = "/u/a/d/adbhat/private/gitRepository/NFS_FUSE_Implementation/server_side/v1/";
//    struct stat stbuf;
//    struct stat stbuf2;
//
//    char * pathPre = strdup(pathPrefix.c_str());
//    char * pathPre2 = strdup(pathPrefix.c_str());
//
//    int retVal = 111;
//
//    cout << strcat(pathPre,"a.txt") << endl;
//    retVal = server.xmp_getattr(pathPre, &stbuf);
//    cout << "returned : " << retVal << endl;
//    printStat(&stbuf);
//
//    cout << strcat(pathPre2,"c.txt") << endl;
//    retVal = server.xmp_getattr(pathPre2, &stbuf2);
//    cout << "returned : " << retVal << endl;
//    printStat(&stbuf2);
//
//
//    return 0;
//}