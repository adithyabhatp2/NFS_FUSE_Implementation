//
// Created by adbhat on 10/14/16.
//

#ifndef V3_RPCCLIENT_H_H
#define V3_RPCCLIENT_H_H

#include <iostream>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <vector>
#include <iomanip>
#include "gen-cpp/Echo.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;


#define BILLION 1000000000L
#define MEGA 1000000L

class RPCClient {
public :
    void clientUsage(void) ;
    string generateRandStr(size_t length);
    vector<string> generateRandomStrings(unsigned long numStrings, unsigned long strLen) ;
    long warmupClock(clockid_t clk_id = CLOCK_MONOTONIC) ;
    void communicatewithServer(char *hostName, int port, unsigned long numPkts, unsigned long msgLen) ;
    void calculateBandwidth(char *hostName, int port, unsigned long numPkts, unsigned long msgLen,
                            clockid_t clk_id = CLOCK_MONOTONIC) ;
};

#endif //V3_RPCCLIENT_H_H
