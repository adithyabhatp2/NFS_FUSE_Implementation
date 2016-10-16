//
// Created by adbhat on 10/15/16.
//

#include<iostream>
#include<fstream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

using namespace std;


void print_client_usage() {
    cout << "<read.o> -p <pathToFileToRead>" << endl;
}


void read_and_print_file(string path) {

    ifstream myReadFile;

    myReadFile.open(path);

    char output[100];
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> output;
            cout << output;
        }
    }
    myReadFile.close();
}

int main(int argc, char **argv) {

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

