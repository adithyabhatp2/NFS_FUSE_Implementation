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
#include <vector>

using namespace std;


void print_client_usage() {
    cout << "<write.o> -p <pathToFileToWrite> -l <len of msg>" << endl;
    exit(0);
}


string generateRandStr(size_t length) {
    static string charset = "0123456789"
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    string result;
    result.resize(length);
    for (size_t i = 0; i < length; i++) {
        result[i] = charset[rand() % charset.length()];
    }
    return result;
}

vector<string> generateRandomStrings(unsigned long numStrings, unsigned long strLen) {
    vector<string> result;
    for (unsigned long i = 0; i < numStrings; i++) {
        result.push_back(generateRandStr(strLen));
    }
    return result;
}


void write_and_fsync_file(char *pathToFile, int size) {

    string msg = generateRandStr(size);

    cout << "Write : " << size << " starts with : " << msg.substr(0, 10) << endl;

    const char * buf = msg.c_str();

    int fd = open(pathToFile, O_CREAT | O_RDWR);

    cout << "FD : "<< fd << endl;

    if(fd <=0) {
        exit(-1);
    }

    write(fd, buf, size);

    fsync(fd);
    close(fd);

}


int main(int argc, char **argv) {

    if (argc != 5) {
        cout << "Wrong number of params, argc : " << argc << endl;
        print_client_usage();
        exit(0);
    }

    char *pathToFile;
    int ch;

    unsigned long msgLen = 10;

    while ((ch = getopt(argc, argv, "p:l:")) != -1) {
        switch (ch) {
            case 'p':
                pathToFile = strdup(optarg);
                break;
            case 'l':
                msgLen = strtoul(optarg, NULL, 10);
                if (msgLen == 0 && errno == EINVAL) {
                    print_client_usage();
                }
                break;
            case '?':
            default:
                print_client_usage();
                return 0;
        }
    }


    write_and_fsync_file(pathToFile, msgLen);

    return 0;
}
