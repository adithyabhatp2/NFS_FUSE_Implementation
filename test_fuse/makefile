

default: readfd writefd writesleep getattr inode

readcpp:
	g++ -std=c++11 read_file_cpp.cpp -o read_file_cpp.o
readfd:
	g++ -std=c++11 read_file_fd.cpp -o read_fd.o
writefd:
	g++ -std=c++11 write_file_fd.cpp -o write_fd.o
writesleep:
	g++ -std=c++11 write_sleep_sync.cpp -o sleep.o
getattr:
	g++ -std=c++11 getattr_file.cpp -o getattr.o
inode:
	g++ -std=c++11 inode_gen.cpp -o inode_gen.o
clean:
	rm *.o
