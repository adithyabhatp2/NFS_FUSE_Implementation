

default: readfd writefd inode

readcpp:
	g++ -std=c++11 read_file_cpp.cpp -o read_file_cpp.o
readfd:
	g++ -std=c++11 read_file_fd.cpp -o read_fd.o
writefd:
	g++ -std=c++11 write_file_fd.cpp -o write_fd.o
inode:
	g++ -std=c++11 inode_gen.cpp -o inode_gen.o
clean:
	rm *.o
