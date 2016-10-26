//
// Created by adbhat on 10/15/16.
//

#include<iostream>
#include<fstream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
# include <unistd.h>
#include <fcntl.h>

using namespace std;

#define BUFSIZE 200
#define DEBUGLEVEL 1


void print_client_usage() {
    cout << "<read.o> -p <pathToFileToRead>" << endl;
}

void read_and_print_file(char *path) {

    int fd = open(path, O_RDONLY);

    cout << "FD : " << fd << endl;

    if (fd <= 0) {
        exit(-1);
    }

    char *buff = (char *) malloc(sizeof(char) * BUFSIZE);
    int actuallyRead = 0;
    int totalRead = 0;
    while ((actuallyRead = read(fd, buff, BUFSIZE)) > 0) {
        if(DEBUGLEVEL <= 1) {
            cout << buff << endl;
            totalRead += actuallyRead;
        }
    }

    if(DEBUGLEVEL <= 1) {
        cout << "total read: " << totalRead << endl;
    }

    close(fd);
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

    read_and_print_file(pathToFile);

    return 0;
}