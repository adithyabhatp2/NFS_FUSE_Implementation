//
// Created by adbhat on 10/26/16.
//

#include<iostream>
#include<fstream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
# include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

#define DEBUGLEVEL 1

void print_client_usage() {
    cout << "<read.o> -p <pathToFileToStat / getattr>" << endl;
}


void printStat(struct stat* stbuf) {
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

void read_and_lstat_file(char *path) {

    struct stat stbuf;

    int retVal = lstat(path, &stbuf);
    if(retVal < 0) {
        printf("lstat failed for path: %s\n", path);
        printf("errno: ", errno);
        exit(0);
    }

    if(DEBUGLEVEL <= 1) {
        cout << "lstat succeeded" << endl;
        printStat(&stbuf);
    }
}


int main(int argc, char **argv) {

    cout << "Reading a file in C-style with FDs" << endl;

    if (argc != 3) {
        cout << "Wrong number of params, argc : " << argc << endl;
        print_client_usage();
        exit(0);
    }

    char *pathToFile;
    int ch;
    while ((ch = getopt(argc, argv, "p:")) != -1) {
        switch (ch) {
            case 'p':
                pathToFile = strdup(optarg);
                break;
        }
    }

    read_and_lstat_file(pathToFile);

    return 0;
}