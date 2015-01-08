/*

	Author: Colby Garland ID# 5034957
	Lab #2
	Purpose: Using pthreads, find the prime numbers from 1 to N, where N is a user entered number, using M number of 	 threads where M is a user-entered number for the number of threads.

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXTHREADS 10 // maximum amount of threads allowed

int numThreads; // number user enters for num of threads
int interval[MAXTHREADS][2]; // holding the start value and end value
int start = 1; // the starting of the thread to find prime
int size; // how big the interval is for each thread
int n; // prime number ending
int threadNumber = 0; // the current thread

int prime(int); // returns a prime number
void *caller();  // calls the prime number function
 
// find the primes
int prime(int number){

	int i;
    	if(number < 2) return 0; 
    	if(number == 2) return number;
    	if(number % 2 == 0) return 0;
    	for(i=3; (i*i)<=number; i+=2) if(number % i == 0) return 0;
    	return number;

}

// calls the prime fucntion with i as a parameter, prints the prime number
void *caller(){
	int i; // for the loop
	int j; // for the second loop
	int numPrimes = 0; // number of primes
	int begin = (int)(interval[threadNumber][0]); 
	int end = (int)(interval[threadNumber][1]);
	threadNumber++;
	for (i = begin; i <= end; i++) if (prime(i)) numPrimes++;
	int primes[numPrimes];
	printf("Thread %d found: ", threadNumber);
	for (j = begin; j <= end; j++) if (prime(j)) printf("%d ",prime(j));
	printf("\n");
}

int main(int argc, char *argv[]){

	if (argc != 3) { // if incorrect usage, informs user with correct usage
		printf("Usage: ./prog <value of N> <# of threads <= %d>\n", MAXTHREADS);
		return -1;
	}

	n = atoi(argv[1]); // n is the prime list max
	numThreads = atoi(argv[2]); // number of threads

	if (numThreads > MAXTHREADS) { // if more than MAXTHREADS
		printf("Cannot have more than %d threads.\n", MAXTHREADS);
		return -1;
	}
	
	pthread_t tid [MAXTHREADS]; // the thread identifier 
	pthread_attr_t attr;

	size = n / numThreads;
	start = 0; // intialize the starting position to 0
	threadNumber = 0;

	int i;
	for (i = 0; i < numThreads; i++){
		interval[i][0] = start;
		interval[i][1] = start + size;
		start += size;
		pthread_attr_init(&attr);	
		pthread_create(&tid[i], NULL, caller, interval[i]);
	}

	for (i = 0; i < numThreads; i++) pthread_join(tid[i],NULL); // wait for the threads to be done

	return 0;
}

