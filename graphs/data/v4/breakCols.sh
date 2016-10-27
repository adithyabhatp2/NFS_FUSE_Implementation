mkdir write
mkdir read
mkdir fsync

for f in v4_100000.txt.txt  v4_10000.txt.txt  v4_1000.txt.txt  v4_100.txt.txt  v4_10.txt.txt  v4_1.txt.txt  v4_20000.txt.txt  v4_40000.txt.txt  v4_60000.txt.txt

do 
	awk -F '\t' '{print $1}' $f > write/$f
	awk -F '\t' '{print $2}' $f > fsync/$f
	awk -F '\t' '{print $3}' $f > read/$f
done

