/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef NfsRpc_TYPES_H
#define NfsRpc_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>




class thrift_timespec;

class thrift_fuse_file_info;

class thrift_stat;

class thrift_statvfs;

typedef struct _thrift_timespec__isset {
  _thrift_timespec__isset() : tv_sec(false), tv_nsec(false) {}
  bool tv_sec :1;
  bool tv_nsec :1;
} _thrift_timespec__isset;

class thrift_timespec {
 public:

  thrift_timespec(const thrift_timespec&);
  thrift_timespec& operator=(const thrift_timespec&);
  thrift_timespec() : tv_sec(0), tv_nsec(0) {
  }

  virtual ~thrift_timespec() throw();
  int64_t tv_sec;
  int64_t tv_nsec;

  _thrift_timespec__isset __isset;

  void __set_tv_sec(const int64_t val);

  void __set_tv_nsec(const int64_t val);

  bool operator == (const thrift_timespec & rhs) const
  {
    if (!(tv_sec == rhs.tv_sec))
      return false;
    if (!(tv_nsec == rhs.tv_nsec))
      return false;
    return true;
  }
  bool operator != (const thrift_timespec &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const thrift_timespec & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(thrift_timespec &a, thrift_timespec &b);

inline std::ostream& operator<<(std::ostream& out, const thrift_timespec& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _thrift_fuse_file_info__isset {
  _thrift_fuse_file_info__isset() : flags(false), fh_old(false), writepage(false), direct_io(false), keep_cache(false), flush(false), nonseekable(false), flock_release(false), padding(false), fh(false), lock_owner(false) {}
  bool flags :1;
  bool fh_old :1;
  bool writepage :1;
  bool direct_io :1;
  bool keep_cache :1;
  bool flush :1;
  bool nonseekable :1;
  bool flock_release :1;
  bool padding :1;
  bool fh :1;
  bool lock_owner :1;
} _thrift_fuse_file_info__isset;

class thrift_fuse_file_info {
 public:

  thrift_fuse_file_info(const thrift_fuse_file_info&);
  thrift_fuse_file_info& operator=(const thrift_fuse_file_info&);
  thrift_fuse_file_info() : flags(0), fh_old(0), writepage(0), direct_io(0), keep_cache(0), flush(0), nonseekable(0), flock_release(0), padding(0), fh(0), lock_owner(0) {
  }

  virtual ~thrift_fuse_file_info() throw();
  int32_t flags;
  int64_t fh_old;
  int32_t writepage;
  int32_t direct_io;
  int32_t keep_cache;
  int32_t flush;
  int32_t nonseekable;
  int32_t flock_release;
  int32_t padding;
  int64_t fh;
  int64_t lock_owner;

  _thrift_fuse_file_info__isset __isset;

  void __set_flags(const int32_t val);

  void __set_fh_old(const int64_t val);

  void __set_writepage(const int32_t val);

  void __set_direct_io(const int32_t val);

  void __set_keep_cache(const int32_t val);

  void __set_flush(const int32_t val);

  void __set_nonseekable(const int32_t val);

  void __set_flock_release(const int32_t val);

  void __set_padding(const int32_t val);

  void __set_fh(const int64_t val);

  void __set_lock_owner(const int64_t val);

  bool operator == (const thrift_fuse_file_info & rhs) const
  {
    if (!(flags == rhs.flags))
      return false;
    if (!(fh_old == rhs.fh_old))
      return false;
    if (!(writepage == rhs.writepage))
      return false;
    if (!(direct_io == rhs.direct_io))
      return false;
    if (!(keep_cache == rhs.keep_cache))
      return false;
    if (!(flush == rhs.flush))
      return false;
    if (!(nonseekable == rhs.nonseekable))
      return false;
    if (!(flock_release == rhs.flock_release))
      return false;
    if (!(padding == rhs.padding))
      return false;
    if (!(fh == rhs.fh))
      return false;
    if (!(lock_owner == rhs.lock_owner))
      return false;
    return true;
  }
  bool operator != (const thrift_fuse_file_info &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const thrift_fuse_file_info & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(thrift_fuse_file_info &a, thrift_fuse_file_info &b);

inline std::ostream& operator<<(std::ostream& out, const thrift_fuse_file_info& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _thrift_stat__isset {
  _thrift_stat__isset() : st_dev(false), st_ino(false), st_mode(false), st_nlink(false), st_uid(false), st_gid(false), __pad0(false), st_size(false), st_blksize(false), st_blocks(false), st_atim(false), st_mtim(false), st_ctim(false), __glibc_reserved0(false), __glibc_reserved1(false), __glibc_reserved2(false) {}
  bool st_dev :1;
  bool st_ino :1;
  bool st_mode :1;
  bool st_nlink :1;
  bool st_uid :1;
  bool st_gid :1;
  bool __pad0 :1;
  bool st_size :1;
  bool st_blksize :1;
  bool st_blocks :1;
  bool st_atim :1;
  bool st_mtim :1;
  bool st_ctim :1;
  bool __glibc_reserved0 :1;
  bool __glibc_reserved1 :1;
  bool __glibc_reserved2 :1;
} _thrift_stat__isset;

class thrift_stat {
 public:

  thrift_stat(const thrift_stat&);
  thrift_stat& operator=(const thrift_stat&);
  thrift_stat() : st_dev(0), st_ino(0), st_mode(0), st_nlink(0), st_uid(0), st_gid(0), __pad0(0), st_size(0), st_blksize(0), st_blocks(0), __glibc_reserved0(0), __glibc_reserved1(0), __glibc_reserved2(0) {
  }

  virtual ~thrift_stat() throw();
  int64_t st_dev;
  int64_t st_ino;
  int32_t st_mode;
  int64_t st_nlink;
  int32_t st_uid;
  int32_t st_gid;
  int32_t __pad0;
  int64_t st_size;
  int64_t st_blksize;
  int64_t st_blocks;
  thrift_timespec st_atim;
  thrift_timespec st_mtim;
  thrift_timespec st_ctim;
  int64_t __glibc_reserved0;
  int64_t __glibc_reserved1;
  int64_t __glibc_reserved2;

  _thrift_stat__isset __isset;

  void __set_st_dev(const int64_t val);

  void __set_st_ino(const int64_t val);

  void __set_st_mode(const int32_t val);

  void __set_st_nlink(const int64_t val);

  void __set_st_uid(const int32_t val);

  void __set_st_gid(const int32_t val);

  void __set___pad0(const int32_t val);

  void __set_st_size(const int64_t val);

  void __set_st_blksize(const int64_t val);

  void __set_st_blocks(const int64_t val);

  void __set_st_atim(const thrift_timespec& val);

  void __set_st_mtim(const thrift_timespec& val);

  void __set_st_ctim(const thrift_timespec& val);

  void __set___glibc_reserved0(const int64_t val);

  void __set___glibc_reserved1(const int64_t val);

  void __set___glibc_reserved2(const int64_t val);

  bool operator == (const thrift_stat & rhs) const
  {
    if (!(st_dev == rhs.st_dev))
      return false;
    if (!(st_ino == rhs.st_ino))
      return false;
    if (!(st_mode == rhs.st_mode))
      return false;
    if (!(st_nlink == rhs.st_nlink))
      return false;
    if (!(st_uid == rhs.st_uid))
      return false;
    if (!(st_gid == rhs.st_gid))
      return false;
    if (!(__pad0 == rhs.__pad0))
      return false;
    if (!(st_size == rhs.st_size))
      return false;
    if (!(st_blksize == rhs.st_blksize))
      return false;
    if (!(st_blocks == rhs.st_blocks))
      return false;
    if (!(st_atim == rhs.st_atim))
      return false;
    if (!(st_mtim == rhs.st_mtim))
      return false;
    if (!(st_ctim == rhs.st_ctim))
      return false;
    if (!(__glibc_reserved0 == rhs.__glibc_reserved0))
      return false;
    if (!(__glibc_reserved1 == rhs.__glibc_reserved1))
      return false;
    if (!(__glibc_reserved2 == rhs.__glibc_reserved2))
      return false;
    return true;
  }
  bool operator != (const thrift_stat &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const thrift_stat & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(thrift_stat &a, thrift_stat &b);

inline std::ostream& operator<<(std::ostream& out, const thrift_stat& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _thrift_statvfs__isset {
  _thrift_statvfs__isset() : f_bsize(false), f_frsize(false), f_blocks(false), f_bfree(false), f_bavail(false), f_files(false), f_ffree(false), f_favail(false), f_fsid(false), f_flag(false), f_namemax(false), __f_spare0(false), __f_spare1(false), __f_spare2(false), __f_spare3(false), __f_spare4(false), __f_spare5(false) {}
  bool f_bsize :1;
  bool f_frsize :1;
  bool f_blocks :1;
  bool f_bfree :1;
  bool f_bavail :1;
  bool f_files :1;
  bool f_ffree :1;
  bool f_favail :1;
  bool f_fsid :1;
  bool f_flag :1;
  bool f_namemax :1;
  bool __f_spare0 :1;
  bool __f_spare1 :1;
  bool __f_spare2 :1;
  bool __f_spare3 :1;
  bool __f_spare4 :1;
  bool __f_spare5 :1;
} _thrift_statvfs__isset;

class thrift_statvfs {
 public:

  thrift_statvfs(const thrift_statvfs&);
  thrift_statvfs& operator=(const thrift_statvfs&);
  thrift_statvfs() : f_bsize(0), f_frsize(0), f_blocks(0), f_bfree(0), f_bavail(0), f_files(0), f_ffree(0), f_favail(0), f_fsid(0), f_flag(0), f_namemax(0), __f_spare0(0), __f_spare1(0), __f_spare2(0), __f_spare3(0), __f_spare4(0), __f_spare5(0) {
  }

  virtual ~thrift_statvfs() throw();
  int64_t f_bsize;
  int64_t f_frsize;
  int64_t f_blocks;
  int64_t f_bfree;
  int64_t f_bavail;
  int64_t f_files;
  int64_t f_ffree;
  int64_t f_favail;
  int64_t f_fsid;
  int64_t f_flag;
  int64_t f_namemax;
  int32_t __f_spare0;
  int32_t __f_spare1;
  int32_t __f_spare2;
  int32_t __f_spare3;
  int32_t __f_spare4;
  int32_t __f_spare5;

  _thrift_statvfs__isset __isset;

  void __set_f_bsize(const int64_t val);

  void __set_f_frsize(const int64_t val);

  void __set_f_blocks(const int64_t val);

  void __set_f_bfree(const int64_t val);

  void __set_f_bavail(const int64_t val);

  void __set_f_files(const int64_t val);

  void __set_f_ffree(const int64_t val);

  void __set_f_favail(const int64_t val);

  void __set_f_fsid(const int64_t val);

  void __set_f_flag(const int64_t val);

  void __set_f_namemax(const int64_t val);

  void __set___f_spare0(const int32_t val);

  void __set___f_spare1(const int32_t val);

  void __set___f_spare2(const int32_t val);

  void __set___f_spare3(const int32_t val);

  void __set___f_spare4(const int32_t val);

  void __set___f_spare5(const int32_t val);

  bool operator == (const thrift_statvfs & rhs) const
  {
    if (!(f_bsize == rhs.f_bsize))
      return false;
    if (!(f_frsize == rhs.f_frsize))
      return false;
    if (!(f_blocks == rhs.f_blocks))
      return false;
    if (!(f_bfree == rhs.f_bfree))
      return false;
    if (!(f_bavail == rhs.f_bavail))
      return false;
    if (!(f_files == rhs.f_files))
      return false;
    if (!(f_ffree == rhs.f_ffree))
      return false;
    if (!(f_favail == rhs.f_favail))
      return false;
    if (!(f_fsid == rhs.f_fsid))
      return false;
    if (!(f_flag == rhs.f_flag))
      return false;
    if (!(f_namemax == rhs.f_namemax))
      return false;
    if (!(__f_spare0 == rhs.__f_spare0))
      return false;
    if (!(__f_spare1 == rhs.__f_spare1))
      return false;
    if (!(__f_spare2 == rhs.__f_spare2))
      return false;
    if (!(__f_spare3 == rhs.__f_spare3))
      return false;
    if (!(__f_spare4 == rhs.__f_spare4))
      return false;
    if (!(__f_spare5 == rhs.__f_spare5))
      return false;
    return true;
  }
  bool operator != (const thrift_statvfs &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const thrift_statvfs & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(thrift_statvfs &a, thrift_statvfs &b);

inline std::ostream& operator<<(std::ostream& out, const thrift_statvfs& obj)
{
  obj.printTo(out);
  return out;
}



#endif
