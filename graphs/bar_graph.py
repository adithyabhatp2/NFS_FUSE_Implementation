#!/usr/bin/env python
import matplotlib.pyplot as plt;

plt.rcdefaults()
import numpy as np
import matplotlib.pyplot as plt

# graph_type="Overhead"
# graph_type="RTT"
# graph_type = "BW"

import os;

def median(lst):
    lst = sorted(lst)
    if len(lst) < 1:
        return None
    if len(lst) % 2 == 1:
        return lst[((len(lst) + 1) / 2) - 1]
    else:
        return float(sum(lst[(len(lst) / 2) - 1:(len(lst) / 2) + 1])) / 2.0


def setGraph(graph_type_var):


    average_or_median = "median"

    pathToGit = "/u/a/d/adbhat/private"
    # path =  "/u/a/d/adbhat/private/gitRepository/NFS_FUSE_Implementation/graphs/data/v4"
    # path = "/u/a/d/adbhat/private/gitRepository/NFS_FUSE_Implementation/graphs/data/cd"
    path = "/u/a/d/adbhat/private/gitRepository/NFS_FUSE_Implementation/graphs/data/1k"

    outDir = "/u/a/d/adbhat/private/gitRepository/NFS_FUSE_Implementation/graphs"

    if not os.path.exists(outDir):
        os.makedirs(outDir)

    xlabels = ('baseline', 'localhost', 'v2', 'v3', 'v4')
    fileNames = ['localsys', 'localhost', 'v2', 'v3', 'v4']

    # xlabels = (10, 100, 1000, 10000, 20000, 40000, 60000, 100000)
    # xlabels = ['10', '100', '1K', '10K', '20K', '40K', '60K', '100K']
    # fileNames = ['10', '100', '1000', '10000', '20000', '40000', '60000', '100000']


    datapoints = []
    stdevs = []

    for fileName in fileNames:

        # filePath = path + "/" + graph_type_var + "/" + str(fileName) + "_cd.txt.txt"
        filePath = path + "/" + graph_type_var + "/" + str(fileName) + "_1000.txt"
        f = open(filePath, 'r')
        bw = []

        for line in f:
            bw.append(float(line))

        '''
        for x in bw:
            print x
        '''

        bw.sort()

        '''
        for x in bw:
            print x
        '''

        if average_or_median == "average":
            # Average graph
            datapoints.append(sum(bw) / len(bw))
        elif average_or_median == "median":
            # Median graph
            datapoints.append((median(bw)/1000000))
        #     millisecs
        else:
            print "Die. niether avg nor median"
        if np.std(bw) < (median(bw)/2):
            stdevs.append((np.std(bw)/1000000))
        else:
            stdevs.append(0)

    # for error bars

    for datapoint in datapoints:
        print datapoint

    outFile = outDir + "/"
    outFile += (graph_type_var + ".png")
    # Font size for plots
    plt.rcParams.update({'font.size': 10})


    y_pos = np.arange(len(xlabels))
    barList = plt.bar(y_pos, datapoints, align='center', yerr=stdevs)

    plt.xticks(y_pos, xlabels)

    for allBar in barList:
        allBar.set_color('g')

        print "Setting labels"
        plt.ylabel('Median Latency (ms)')
        plt.title(graph_type_var)

        plt.xlabel("FUSE-NFS variations")
        # plt.xlabel("Message size in bytes")

    my_dpi = 96;


    plt.autoscale(enable=True)
    plt.ylim(ymin=0)
    plt.savefig(outFile)
    # plt.savefig(outFile, dpi = my_dpi*2)
    plt.show()
    plt.clf()


def main():
    # for graph_type_var in ["MKDIR", "RMDIR", "CREATE", "STAT", "CLOSE", "UNLINK"]:
    for graph_type_var in ["write", "fsync", "read"]:
        setGraph(graph_type_var)


if __name__ == '__main__':
    main()
