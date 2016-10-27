mkdir MKDIR
mkdir RMDIR
mkdir CREATE
mkdir STAT
mkdir CLOSE
mkdir UNLINK

for f in localhost_cd.txt.txt localsys_cd.txt.txt v2_cd.txt.txt v3_cd.txt.txt v4_cd.txt.txt
do 
	awk -F '\t' '{print $1}' $f > MKDIR/$f
	awk -F '\t' '{print $2}' $f > RMDIR/$f
	awk -F '\t' '{print $3}' $f > CREATE/$f
	awk -F '\t' '{print $4}' $f > STAT/$f
	awk -F '\t' '{print $5}' $f > CLOSE/$f
	awk -F '\t' '{print $6}' $f > UNLINK/$f

done

