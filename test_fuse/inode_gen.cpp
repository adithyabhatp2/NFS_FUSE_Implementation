//
// Created by adbhat on 10/26/16.
//


#include <sys/ioctl.h>
#include <sys/fcntl.h>
#include <linux/fs.h>
#include <stdio.h>
#include <errno.h>

#include<iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
# include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;




void get_file_inode_and_generation(char * pathToFile) {

    int fileno = open(pathToFile, O_RDONLY);

    if(fileno < 0) {
        printf("open failed for path: %s\n", pathToFile);
        exit(0);
    }
    printf("fileno (fd) : %d\n", fileno);

    struct stat stbuf;

    int res = lstat(pathToFile, &stbuf);
    if(res < 0) {
        printf("lstat failed for path: %s\n", pathToFile);
        exit(0);
    }
    printf("device id : %ld\n", stbuf.st_dev);
    printf("inode : %ld\n", stbuf.st_ino);

    int generation = 0;
    if (ioctl(fileno, FS_IOC_GETVERSION, &generation)) {
        printf("errno: %d\n", errno);
    }
    printf("generation: %d\n", generation);

}


void print_client_usage() {
    cout << "<read.o> -p <pathToFileToRead>" << endl;
}


int main(int argc, char **argv) {


    cout << "Reading a file's Inode and Gen" << endl;

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

    get_file_inode_and_generation(pathToFile);

    return 0;
}