# makefile for lab 2 for cs3790
# makefile for the pthreads part
# program by Colby Garland id# 5034957
# gcc -lpthread to compile

prog: pthreads.o
	gcc -pthread pthreads.o -o prog

pthreads.o: pthreads.c
	gcc -pthread -c pthreads.c

clean:
	rm -rf *.o prog
