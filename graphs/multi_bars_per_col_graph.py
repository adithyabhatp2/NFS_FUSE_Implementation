#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
import os;


def median(lst):
    lst = sorted(lst)
    if len(lst) < 1:
        return None
    if len(lst) % 2 == 1:
        return lst[((len(lst) + 1) / 2) - 1]
    else:
        return float(sum(lst[(len(lst) / 2) - 1:(len(lst) / 2) + 1])) / 2.0


def getList(path, fileNames, average_or_median, factor=1):
    setData = []
    set_stdDev = []

    for fileName in fileNames:

        fileBW = path + "/" + str(fileName)
        f = open(fileBW, 'r')
        data = []

        fileName.split()

        for line in f:
            data.append(float(line)*factor/1000)


        '''
        for x in bw:
            print x
        '''

        data.sort()

        '''
        for x in bw:
            print x
        '''

        if average_or_median == "average":
            # Average graph
            setData.append(sum(data) / len(data))
        elif average_or_median == "median":
            # Median graph
            setData.append(median(data))
        else:
            print "Die. niether avg nor median"
        set_stdDev.append(np.std(data))
        print fileName + "\tstdDev: " + str(np.std(data)) + "\tMedian : " + str(median(data))

    for data_point in setData:
        print data_point

    return setData, set_stdDev



def setGraph():

    local_or_remote = "remote"
    optimized_or_not = "_o" #or empty
    average_or_median = "median"

    pathSet0 = "/u/a/d/adbhat/private/gitRepository/739_A1/part2/results/opt/diff_mach"
    pathSet1 = "/u/a/d/adbhat/private/gitRepository/739_A1/part3/grpc/results/opt/non-streaming/different_machine"
    pathSet2 = "/u/a/d/adbhat/private/gitRepository/739_A1/part3/thrift/Echo/v3/results_remote_o"

    fileNames0 = ['10_Rtt.log', '100_Rtt.log', '1000_Rtt.log', '10000_Rtt.log', '20000_Rtt.log', '40000_Rtt.log']
    fileNames1 = ['RTT_10.log', 'RTT_100.log', 'RTT_1000.log', 'RTT_10000.log', 'RTT_20000.log', 'RTT_40000.log']
    fileNames2 = ['10_RTT.txt', '100_RTT.txt', '1000_RTT.txt', '10000_RTT.txt', '20000_RTT.txt', '40000_RTT.txt']
    objects = ('10B', '100B', '1KB', '10KB', '20KB', '40KB', '60KB')

    masterSet0, masterLstSet0 = getList(pathSet0, fileNames0, average_or_median, 1000)
    masterSet1, masterLstSet1 = getList(pathSet1, fileNames1, average_or_median, 1)
    masterSet2, masterLstSet2 = getList(pathSet2, fileNames2, average_or_median, 1)

    N = len(masterSet1)
    set1 = (masterSet1)
    set1_stdDev = (masterLstSet1)

    set2 = (masterSet2)
    set2_stdDev = (masterLstSet2)

    set0 = (masterSet0)
    set0_stdDev = (masterLstSet0)

    ind = np.arange(N)  # the x locations for the groups
    # width = 0.35  # the width of the bars
    width = 0.25

    fig, ax = plt.subplots()

    rects1 = ax.bar(ind, set1, width, color='r', yerr=set1_stdDev)
    rects2 = ax.bar(ind + width, set2, width, color='y', yerr=set2_stdDev)
    rects0 = ax.bar(ind + width + width, set0, width, color='b', yerr=set0_stdDev)

    print "RTT - GRPC vs Thrift vs UDP"
    ax.set_ylabel('Time (us)')
    ax.set_title('RTT - GRPC vs Thrift vs UDP')
    plt.xlabel("Message Size (Bytes)")
    ax.legend((rects1[0], rects2[0], rects0[0]), ('GRPC', 'Thrift', 'UDP'), loc = 2)
    outFile = "RTT_grpc_vs_thrift_udp.png"

    # add some text for labels, title and axes ticks
    ax.set_xticks(ind + width)
    ax.set_xticklabels(objects)

    def autolabel(rects):
        # attach some text labels
        for rect in rects:
            height = rect.get_height()
            ax.text(rect.get_x() + rect.get_width() / 3., 1.05 * height, '%d' % int(height), ha='center', va='bottom')

    # autolabel(rects0)
    # autolabel(rects1)
    # autolabel(rects2)

    plt.autoscale(enable=True)
    plt.ylim(ymin=0)
    plt.savefig(outFile)
    plt.show()
    plt.clf()


def graphFromData():
    set1 = (130, 19, 73, 20)
    set1_stdDev = (2.73, 1.68, 12.68, 3.58)

    set2 = (132, 20, 75, 23)
    set2_stdDev = (2.90, 1.16, 9.72, 3.49)

    N = 4
    ind = np.arange(N)

    fig, ax = plt.subplots()
    rects1 = ax.bar(ind, set1, width, color='r', yerr=set1_stdDev)
    rects2 = ax.bar(ind + width, set2, width, color='y', yerr=set2_stdDev)

    objects = ('realtime', 'monotonic', 'monotonic_raw', 'cpu_process_cputime')
    print "gettime() - Clock Evaluation"
    ax.set_ylabel('Time (ns)')
    ax.set_title('gettime() - Clock Evaluation')
    outFile = "RTTandOverhead.png"
    plt.xlabel("Clock_id")
    ax.legend((rects1[0], rects2[0]), ('Baseline', 'With minimal instructions'), loc='top right')

    # add some text for labels, title and axes ticks
    ax.set_xticks(ind + width)
    ax.set_xticklabels(objects)

    def autolabel(rects):
        # attach some text labels
        for rect in rects:
            height = rect.get_height()
            ax.text(rect.get_x() + rect.get_width() / 2., 1.05 * height, '%d' % int(height), ha='center', va='bottom')

    plt.autoscale(enable=True)
    plt.ylim(ymin=0)
    # plt.savefig(outFile)
    plt.show()
    plt.clf()


def main():
    setGraph()


if __name__ == '__main__':
    main()
