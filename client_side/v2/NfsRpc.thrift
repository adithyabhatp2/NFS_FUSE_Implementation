
struct thrift_timespec {
	1: i64 tv_sec;
    2: i64 tv_nsec;
}

struct thrift_fuse_file_info {
    1: i32 flags;
    2: i64 fh_old;
    3: i32 writepage;
    4: i32 direct_io;
    5: i32 keep_cache;
    6: i32 flush;
    7: i32 nonseekable;
    8: i32 flock_release;
    9: i32 padding;
    10: i64 fh;
    11: i64 lock_owner;
}

struct thrift_stat {
	1: i64 st_dev;
	2: i64 st_ino;
	3: i32 st_mode;
	4: i64 st_nlink;
	5: i32 st_uid;
	6: i32 st_gid;
	7: i32 __pad0;
	8: i64 st_size;
	9: i64 st_blksize;
	10: i64 st_blocks;
	11: thrift_timespec st_atim;
	12: thrift_timespec st_mtim;
	13: thrift_timespec st_ctim;
	14: i64 __glibc_reserved0;
	15: i64 __glibc_reserved1;
	16: i64 __glibc_reserved2;
	17: i64 st_rdev;
}

struct thrift_statvfs {
    1: i64 f_bsize;
    2: i64 f_frsize;
    3: i64 f_blocks;
    4: i64 f_bfree;
    5: i64 f_bavail;
    6: i64 f_files;
    7: i64 f_ffree;
    8: i64 f_favail;
	9: i64 f_fsid;
    10: i64 f_flag;
    11: i64 f_namemax;
    12: i32 __f_spare0;
    13: i32 __f_spare1;
    14: i32 __f_spare2;
    15: i32 __f_spare3;
    16: i32 __f_spare4;
    17: i32 __f_spare5;
}

struct thrift_getattr_reply {
    1: i32 retVal;
    2: thrift_stat tstbuf;
}

struct thrift_read_reply {
    1: i32 retVal;
    2: string tbuf;
}

struct thrift_statfs_reply {
    1: i32 retVal;
    2: thrift_statvfs tstbuf;
}

struct thrift_open_reply {
    1: i32 retVal;
    2: thrift_fuse_file_info tfi;
}

struct thrift_readlink_reply {
    1: i32 retVal;
    2: string tbuf;
}

struct thrift_fsync_reply {
    1: i32 retVal;
    2: i32 isdatasync;
    3: thrift_fuse_file_info tfi;
}

struct thrift_dir_entry {
    1: i64 d_ino;
    2: i64 d_type;
    3: string d_name;
}

struct thrift_readdir_reply {
    1: i32 retVal;
    2: list<thrift_dir_entry> dir_entries;
}

service NfsRpc {

    i32 xmp_create(1:string tpath, 2:i32 mode, 3:thrift_fuse_file_info tfi)
    i32 xmp_unlink(1:string tpath);
    thrift_getattr_reply xmp_getattr(1:string tpath, 2:thrift_stat stbuf);
    i32 xmp_setattr(1:string tpath, 2:thrift_stat stbuf);
    thrift_read_reply xmp_read(1:string tpath, 2:string tbuf, 3:i64 size, 4:i64 offset, 5:thrift_fuse_file_info tfi);
    i32 xmp_write(1:string tpath, 2:string tbuf, 3:i64 size, 4:i64 offset, 5:thrift_fuse_file_info tfi);
    i32 xmp_rename(1:string tfrom, 2:string tto);
    i32 xmp_mkdir(1:string tpath, 2:i32 mode);
    i32 xmp_rmdir(1:string tpath);

    thrift_readdir_reply xmp_readdir(1:string tpath, 2:i64 offset, 3:thrift_fuse_file_info tfi);

    thrift_statfs_reply xmp_statfs(1:string tpath, 2:thrift_statvfs tstbuf);

    thrift_open_reply xmp_open(1:string tpath, 2:thrift_fuse_file_info tfi);
    i32 xmp_access(1:string tpath, 2:i32 mask);
    i32 xmp_mknod(1:string tpath, 2:i32 mode, 3:i64 rdev);

    thrift_readlink_reply xmp_readlink(1:string tpath, 2:string tbuf, 3:i64 size);
    i32 xmp_symlink(1:string tfrom, 2:string tto);
    i32 xmp_link(1:string tfrom, 2:string tto);
    i32 xmp_chmod(1:string tpath, 2:i32 mode);
    i32 xmp_chown(1:string tpath, 2:i32 uid, 3:i32 gid);
    i32 xmp_truncate(1:string tpath, 3:i64 size);
    i32 xmp_release(1:string tpath, 2:thrift_fuse_file_info tfi);
    thrift_fsync_reply xmp_fsync(1:string tpath, 2:i32 isdatasync, 3:thrift_fuse_file_info tfi);
}

