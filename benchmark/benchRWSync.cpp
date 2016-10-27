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
#include<iostream>
#include<fstream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
# include <unistd.h>
#include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <assert.h>
# include <ctype.h>
# include <errno.h>
# include <limits.h>

#define BILLION 1000000000L

using namespace std;

#define DEBUGLEVEL 1

void print_client_usage() {
    cout << "<bench.o> -p <pathToFile> -l <len of msg> -n <numReps> " << endl;
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


void printTimeElapsed(struct timespec tp_start, struct timespec tp_end) {
    long time_elapsed_sec = (tp_end.tv_sec - tp_start.tv_sec);
    long time_elapsed_nsec = (tp_end.tv_nsec - tp_start.tv_nsec);
    printf("%ld", (BILLION * time_elapsed_sec) + time_elapsed_nsec);
}


void bench_file(char *pathToFile, unsigned long msgLen, unsigned long numLoops, clockid_t clk_id = CLOCK_MONOTONIC) {

    struct timespec tp_start, tp_end, res;
    long time_elapsed_sec;
    long time_elapsed_nsec;

    cout << "Bench : " << pathToFile << " : len : " << msgLen << " loops : " << numLoops << endl;

    cout << "WRITE\tFSYNC\tREAD\n";

    int fd = open(pathToFile, O_CREAT | O_RDWR, S_IRWXO|S_IRWXG | S_IRWXU);

    if(fd <=0) {
        cout << "Failed to open file.." << fd << endl;
        exit(-1);
    }
//    cout << "FD : "<< fd << endl;

    unsigned long i;

    ssize_t retVal;

    char *read_buf = (char *) malloc(sizeof(char) * msgLen);
    if(read_buf == NULL) {
        cout << "error in malloc " << errno << endl;
    }

    for(i=0;i<numLoops;i++) {
        string msg = generateRandStr(msgLen);
        const char * write_buf = msg.c_str();

        struct stat stbuf;

        //WRITE
        retVal = lseek(fd, 0, SEEK_SET);
        if(retVal <0) {
            cout << "lseek failed errno :  " << errno << endl;
        }
        clock_gettime(clk_id, &tp_start);
        retVal = write(fd, write_buf, msgLen);
        clock_gettime(clk_id, &tp_end);

        printTimeElapsed(tp_start, tp_end);
        cout << "\t";
        if(retVal < 0) {
            cout << "ERROR in write" << endl;
        }


        //FSYNC
        clock_gettime(clk_id, &tp_start);
        retVal = fsync(fd);
        clock_gettime(clk_id, &tp_end);

        printTimeElapsed(tp_start, tp_end);
        cout << "\t";
        if(retVal < 0) {
            cout << "ERROR in fsync" << endl;
        }

        //READ
        retVal = lseek(fd, 0, SEEK_SET);
        if(retVal <0) {
            cout << "lseek failed errno :  " << errno << endl;
        }
        clock_gettime(clk_id, &tp_start);
        retVal = read(fd, read_buf, msgLen);
        clock_gettime(clk_id, &tp_end);

        printTimeElapsed(tp_start, tp_end);
        cout << "\t";
        if(retVal < 0) {
            cout << "ERROR in read " << errno << endl;
        }


        cout << endl;
    }

    close(fd);

}


int main(int argc, char **argv) {

    if (argc != 7) {
        cout << "Wrong number of params, argc : " << argc << endl;
        print_client_usage();
        exit(0);
    }

    char *pathToFile;
    int ch;

    unsigned long msgLen = 10;
    unsigned long numLoops = 10;

    while ((ch = getopt(argc, argv, "p:l:n:")) != -1) {
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
            case 'n':
                numLoops = strtoul(optarg, NULL, 10);
                if (numLoops == 0 && errno == EINVAL) {
                    print_client_usage();
                }
                break;
            case '?':
            default:
                print_client_usage();
                return 0;
        }
    }


    bench_file(pathToFile, msgLen, numLoops);

    return 0;
}
