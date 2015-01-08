/*
	Author: Colby Garland
	Assignment #1: Fork and Exec
	Purpose: The parent forks 3 child processes, which then exec and start their respective programs

*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

enum status { on, off};
typedef enum status status;
char *argv[2] = {"~/Documents/cs3790/assign1/", NULL}; 

unsigned  i = 0;
status flag = on;
int pid [3];
int current = 0;

struct sigaction newhandler, oldhandler;
sigset_t sig;

// signal handler, kills one process and starts another
void next( int code){

	kill (pid[current], SIGSTOP);
	current++;
	if (current == 3) current = 0;
	kill (pid[current], SIGCONT);

}

void main(){

 	pid[0] = fork();
	if (pid[0] == 0) // child one 
		execv("child1", argv);
	else {
		pid[1] = fork();
		if (pid[1] == 0) // child two
			execv("child2", argv);
		else {
			pid[2] = fork();
			if (pid[2] == 0) // child three
				execv("child3", argv);
			else {
				// parent process continues from here
        			sigemptyset(&sig);  /* clear the signal mask */
        			newhandler.sa_handler = next;
        			newhandler.sa_mask = sig;
        			newhandler.sa_flags = 0;

        			if ( sigaction(SIGALRM,&newhandler,&oldhandler) == -1 ) {		
            				printf("1 - can't install signal handler \n");
            				exit(-1);
          			}
        			while (1) { // puts parent to sleep, wakes and recalls signal handler
          				alarm(3);
          				pause();
	
        			}
        		}
		}
	}
}

