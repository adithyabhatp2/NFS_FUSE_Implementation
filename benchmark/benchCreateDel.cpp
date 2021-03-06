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
    cout << "<bench.o> -p <pathToDirWithout/> -l <len of msg> -n <numReps> " << endl;
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


void bench_file(char *pathToDir, unsigned long msgLen, unsigned long numLoops, clockid_t clk_id = CLOCK_MONOTONIC) {

    struct timespec tp_start, tp_end, res;
    long time_elapsed_sec;
    long time_elapsed_nsec;

    cout << "Bench : " << pathToDir << " : len : " << msgLen << " loops : " << numLoops << endl;


    cout << "1 pathToDir : " << pathToDir << endl;
    string dirPath2 = string(pathToDir);
    cout << "2 pathToDir : " << pathToDir << endl;
    string filePath2 = string(pathToDir);

    cout << "BeforeCat Dir : " << dirPath2 << " \nFile : " << filePath2 << endl;

    dirPath2+="/zzzTempDir";
    filePath2+="/zzzTempFile";

    cout << "AfterCat Dir : " << dirPath2 << " \nFile : " << filePath2 << endl;

    const char * dirPath = dirPath2.c_str();
    const char * filePath = filePath2.c_str();

    cout << "MKDIR\tRMDIR\tCREATE\tSTAT\tCLOSE\tUNLINK\n";


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


        //MKDIR
        clock_gettime(clk_id, &tp_start);
        retVal = mkdir(dirPath, S_IRWXO|S_IRWXG | S_IRWXU);
        clock_gettime(clk_id, &tp_end);
        if(retVal <0) {
            cout << "mkdir failed errno :  " << errno << endl;
        }

        printTimeElapsed(tp_start, tp_end);
        cout << "\t";
        if(retVal < 0) {
            cout << "ERROR in mkdir " << errno << endl;
        }


        //RMDIR
        clock_gettime(clk_id, &tp_start);
        retVal = rmdir(dirPath);
        clock_gettime(clk_id, &tp_end);
        if(retVal <0) {
            cout << "mkdir failed errno :  " << errno << endl;
        }

        printTimeElapsed(tp_start, tp_end);
        cout << "\t";
        if(retVal < 0) {
            cout << "ERROR in rmdir " << errno << endl;
        }


        //CREATE
        clock_gettime(clk_id, &tp_start);
        int fd = open(filePath, O_CREAT | O_WRONLY, S_IRWXO|S_IRWXG | S_IRWXU);
        clock_gettime(clk_id, &tp_end);

        printTimeElapsed(tp_start, tp_end);
        cout << "\t";
        if(fd <=0) {
            cout << "Failed to open file.. ERROR " << errno << endl;
        }



        //STAT
        clock_gettime(clk_id, &tp_start);
        retVal = lstat(filePath, &stbuf);
        clock_gettime(clk_id, &tp_end);

        printTimeElapsed(tp_start, tp_end);
        cout << "\t";
        if(retVal < 0) {
            cout << "ERROR in stat" << endl;
        }

        //WRITE
        retVal = lseek(fd, 0, SEEK_SET);
        if(retVal <0) {
            cout << "lseek failed errno :  " << errno << endl;
        }
        retVal = write(fd, write_buf, msgLen);
        if(retVal < 0) {
            cout << "ERROR in write" << endl;
        }
        fsync(fd);


        //CLOSE
        clock_gettime(clk_id, &tp_start);
        retVal = close(fd);
        clock_gettime(clk_id, &tp_end);

        printTimeElapsed(tp_start, tp_end);
        cout << "\t";
        if(retVal < 0) {
            cout << "ERROR in CLOSE " << errno << endl;
        }


        //UNLINK
        clock_gettime(clk_id, &tp_start);
        retVal = unlink(filePath);
        clock_gettime(clk_id, &tp_end);

        printTimeElapsed(tp_start, tp_end);
        cout << "\t";
        if(retVal < 0) {
            cout << "ERROR in UNLINK " << errno << endl;
        }

        cout << endl;
    }

}


int main(int argc, char **argv) {

    if (argc != 7) {
        cout << "Wrong number of params, argc : " << argc << endl;
        print_client_usage();
        exit(0);
    }

    char *pathToDir;
    int ch;

    unsigned long msgLen = 10;
    unsigned long numLoops = 10;

    while ((ch = getopt(argc, argv, "p:l:n:")) != -1) {
        switch (ch) {
            case 'p':
                pathToDir = strdup(optarg);
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


    bench_file(pathToDir, msgLen, numLoops);

    return 0;
}
