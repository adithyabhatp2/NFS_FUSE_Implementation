#!/usr/bin/env bash


outDir=~/gitRepository/NFS_FUSE_Implementation/results

rm -rf $outDir 
mkdir $outDir

cd ~/gitRepository/NFS_FUSE_Implementation/benchmark
make



#localsys

runDir=~/gitRepository/NFS_FUSE_Implementation/benchmark
./benchCd.o -p $runDir -l 1000 -n 1000 > $outDir/localsys_cd.txt

for msgLen in 1 10 100 1000 10000 20000 40000 60000 100000
do
    echo msgLen $msgLen
    ./benchRws.o -p $runDir/zzzTemp.txt -l $msgLen -n 1000 > $outDir/localsys_$msgLen.txt
done


#localhost

runDir=~/gitRepository/NFS_FUSE_Implementation/client_side/v4/mtpt
./benchCd.o -p $runDir -l 1000 -n 1000 > $outDir/localhost_cd.txt

for msgLen in 1 10 100 1000 10000 20000 40000 60000 100000
do
    echo msgLen $msgLen
    ./benchRws.o -p $runDir/zzzTemp.txt -l $msgLen -n 1000 > $outDir/localhost_$msgLen.txt
done

