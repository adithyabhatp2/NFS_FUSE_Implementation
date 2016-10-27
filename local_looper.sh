#!/usr/bin/env bash


outDir=~/private/gitRepository/NFS_FUSE_Implementation/results

rm -rf $outDir 
mkdir $outDir

cd ~/private/gitRepository/NFS_FUSE_Implementation/benchmark
make

#localsys
runDir=~/private/gitRepository/NFS_FUSE_Implementation/benchmark
./benchCd.o -p $runDir -l 1000 -n 10 > $outDir/localsys_cd.txt

#for msgLen in 1 10 100 1000
for msgLen in 1 10 100 1000 10000 20000 40000 60000 100000
do
    echo msgLen $msgLen
	./benchRws.o -p $runDir/zzzTemp.txt -l $msgLen -n 10 > $outDir/localsys_$msgLen.txt
done



