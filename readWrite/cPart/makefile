# makefile for assinment 2 for cs3790
# makefile for the pthreads part
# program by Colby Garland id# 5034957
# gcc -lpthread to compile

prog: readWrite.o
	gcc -pthread readWrite.o -o prog

readWrite.o: readWrite.c
	gcc -pthread -c readWrite.c

clean:
	rm -rf *.o prog
