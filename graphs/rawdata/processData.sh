
#mkdir ../data/v4

#for f in v4_1.txt v4_10.txt v4_100.txt v4_1000.txt v4_10000.txt v4_20000.txt v4_40000.txt v4_60000.txt v4_100000.txt
#do
#	tail -1000 v4/$f > ../data/v4/$f.txt
#done

for f in localhost_cd.txt  localsys_cd.txt  v2_cd.txt  v3_cd.txt  v4_cd.txt
do
	tail -n +9 cd/$f > ../data/cd/$f.txt
done
