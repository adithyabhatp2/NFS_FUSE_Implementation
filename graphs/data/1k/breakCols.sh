mkdir write
mkdir read

for f in localhost_1000.txt  localsys_1000.txt  v2_1000.txt  v3_1000.txt  v4_1000.txt
do 
	awk -F '\t' '{print $1}' $f > write/$f
	awk -F '\t' '{print $2}' $f > fsync/$f
	awk -F '\t' '{print $3}' $f > read/$f
done

