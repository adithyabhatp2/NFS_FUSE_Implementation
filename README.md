# NFS_FUSE_Implementation

You'll be building a simple distributed file system. The file system will assume an NFS-like protocol; Your file system will integrate into the Linux client side using FUSE.

Building FUSE
--------------

restricted access in CSL machines. use ./configure --prefix="~/..."
configure: MOUNT_FUSE_PATH env var not set, using default /sbin
configure: UDEV_RULES_PATH env var not set, using default /etc/udev/rules.d
configure: INIT_D_PATH env var not set, using default /etc/init.d

Action - set all to /u/a/d/adbhat/Software/<appropriate>

Libraries have been installed in:
   /u/a/d/adbhat/Software/lib

If you ever happen to want to link against installed libraries
in a given directory, LIBDIR, you must either use libtool, and
specify the full pathname of the library, or use the `-LLIBDIR'
flag during linking and do at least one of the following:
   - add LIBDIR to the `LD_LIBRARY_PATH' environment variable
     during execution
   - add LIBDIR to the `LD_RUN_PATH' environment variable
     during linking
   - use the `-Wl,-rpath -Wl,LIBDIR' linker flag
   - have your system administrator add LIBDIR to `/etc/ld.so.conf'

Action - in ~/.bashrc
# adding for cs739 Distbtd p2
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/u/a/d/adbhat/Software/lib
export LD_RUN_PATH=$LD_RUN_PATH:/u/a/d/adbhat/Software/lib
export MOUNT_FUSE_PATH=/u/a/d/adbhat/Software/sbin
export UDEV_RULES_PATH=/u/a/d/adbhat/Software/etc/udev
export INIT_D_PATH=/u/a/d/adbhat/Software/etc
export PATH=$PATH:/u/a/d/adbhat/Software/bin
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/u/a/d/adbhat/Software/lib/pkgconfig
