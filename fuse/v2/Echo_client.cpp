


#include "RPCClient.h"



#define DEBUGLEVEL 1


void RPCClient::clientUsage(void) {
    printf("usage: client -s <server name> -p <port> -n <num pkts> -l <msg length>\n");
    exit(1);
}

string RPCClient::generateRandStr(size_t length) {
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

vector<string> RPCClient::generateRandomStrings(unsigned long numStrings, unsigned long strLen) {
    vector<string> result;
    for (unsigned long i = 0; i < numStrings; i++) {
        result.push_back(generateRandStr(strLen));
    }
    return result;
}

long RPCClient::warmupClock(clockid_t clk_id ) {

    // Just to warm up stuff

    struct timespec tp_start, tp_end;
    long time_elapsed_sec;
    long time_elapsed_nsec;
    long time_elapsed;

    clock_gettime(clk_id, &tp_start);
    // code
    clock_gettime(clk_id, &tp_end);

    time_elapsed_sec = (tp_end.tv_sec - tp_start.tv_sec);
    time_elapsed_nsec = (tp_end.tv_nsec - tp_start.tv_nsec);
    time_elapsed = ((BILLION * time_elapsed_sec) + time_elapsed_nsec);

    return time_elapsed;
}

void RPCClient::communicatewithServer(char *hostName, int port, unsigned long numPkts, unsigned long msgLen) {

    vector<string> msgPackets = generateRandomStrings(numPkts, msgLen);

    boost::shared_ptr<TTransport> socket(new TSocket(hostName, port));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    EchoClient client(protocol);

    try {
        transport->open();

        for (string msg : msgPackets) {
            string returnVal;

            client.echo(returnVal, msg);
            client.send(msg);

            if (DEBUGLEVEL) {
                cout << "Echoing: " << returnVal << endl;
            }
        }
        transport->close();

    } catch (TException &tx) {
        cout << "ERROR: " << tx.what() << endl;
    }
}


void RPCClient::calculateBandwidth(char *hostName, int port, unsigned long numPkts, unsigned long msgLen,
                        clockid_t clk_id ) {

    cout << "server " << hostName << " port " << port << endl;
    cout << "Sending strings of " << msgLen << " size " << numPkts << " times" << endl;
    cout << "String - "<< msgLen << "\t" << "String - "<< msgLen<< endl;
    cout << "RTT\tBW\tSending Overhead"<< endl;

    boost::shared_ptr<TTransport> socket(new TSocket(hostName, port));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    EchoClient client(protocol);

    // Timing Stuff
    struct timespec tp_start, tp_end;
    long time_elapsed_sec;
    long time_elapsed_nsec;
    long time_elapsed;
    long time_elapsed_oneway;

    // 2 decimals
    std::cout << std::fixed;
    std::cout << std::setprecision(2);

    try {
        transport->open();

        uint i = 0;
        for (i = 0; i < numPkts; i++) {

            warmupClock(clk_id);
            string msg = generateRandStr(msgLen);

            clock_gettime(clk_id, &tp_start);
            client.send(msg);
            clock_gettime(clk_id, &tp_end);

            time_elapsed_sec = (tp_end.tv_sec - tp_start.tv_sec);
            time_elapsed_nsec = (tp_end.tv_nsec - tp_start.tv_nsec);
            time_elapsed = ((BILLION * time_elapsed_sec) + time_elapsed_nsec);

            double bandwidth = ((double)msgLen*8.0*(double)BILLION)/((double)time_elapsed*(double)MEGA);


            clock_gettime(clk_id, &tp_start);
            client.oneway_send(msg);
            clock_gettime(clk_id, &tp_end);

            time_elapsed_sec = (tp_end.tv_sec - tp_start.tv_sec);
            time_elapsed_nsec = (tp_end.tv_nsec - tp_start.tv_nsec);
            time_elapsed_oneway = ((BILLION * time_elapsed_sec) + time_elapsed_nsec);

            cout << time_elapsed << "\t" << bandwidth << "\t" << time_elapsed_oneway << endl;
        }

        transport->close();

    } catch (TException &tx) {
        cout << "ERROR: " << tx.what() << endl;
    }

//    cout << " DONE : Sending strings of " << msgLen << " size " << numPkts << " times" << endl;
}


int main(int argc, char *argv[]) {

    RPCClient client;

    if (argc < 9) {
        printf("Insufficient parameters!\n");
        client.clientUsage();
    }

    unsigned long int serverPort = UINT_MAX;
    unsigned long numPkts = 10;
    unsigned long msgLen = 10;

    char *hostName;
    int ch;

    // Read input params from cmd line
    while ((ch = getopt(argc, argv, "s:p:n:l:")) != -1) {
        switch (ch) {
            case 's':
                hostName = strdup(optarg);
                break;
            case 'p':
                serverPort = strtoul(optarg, NULL, 10);
                if (serverPort <= 1024 || serverPort > 65536) {
                    printf("Invalid Port\n");
                    client.clientUsage();
                }
                break;
            case 'n':
                numPkts = strtoul(optarg, NULL, 10);
                if (numPkts == 0 && errno == EINVAL) {
                    client.clientUsage();
                }
                break;
            case 'l':
                msgLen = strtoul(optarg, NULL, 10);
                if (msgLen == 0 && errno == EINVAL) {
                    client.clientUsage();
                }
                break;
            case '?':
            default:
                client.clientUsage();
                return 0;
        }
    }


//    communicatewithServer(hostName, serverPort, numPkts, msgLen);


//    char exitCh = 0;
//    cin >> exitCh;

    client.calculateBandwidth(hostName, serverPort, numPkts, msgLen, CLOCK_MONOTONIC);
}
