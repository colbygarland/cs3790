import java.util.*;
import java.lang.Thread;


/*

	Author: Colby Garland ID# 5034957
	Lab #2
	Purpose: Using java threads, find the prime numbers from 1 to N, where N is a user entered number, using M 		number of threads where M is a user-entered number for the number of threads.

*/




class Prime implements Runnable {
	
	static final int MAXTHREADS = 10; // the max number of threads the user can enter
	static int [][] interval = new int[MAXTHREADS][2]; // holding the start value and end value
	static int start = 0; // the starting of the thread to find prime
	static int size; // how big the interval is for each thread
	static int n; // prime number ending
	static int threadNumber = 0; // the current thread
	static int numThreads; // number user enters for num of threads

	public void run(){

		caller();

	} 
		
	public Prime(){ // constructor

		start = 0;
		size = 0;	
		threadNumber = 0;

	}

	/*
		returns the number if prime, 0 if not	
	*/
	public int prime(int number){

		int i;
    		if(number < 2) return 0; 
    		if(number == 2) return number;
    		if(number % 2 == 0) return 0;
    		for(i=3; (i*i)<=number; i+=2) if(number % i == 0 ) return 0;
    		return number;

	}

	/*
		calls the prime fucntion with i as a parameter, prints the prime number
	*/
	public void caller(){

		int numPrimes = 0; // number of primes
		int begin = (int)(interval[threadNumber][0]); 
		int end = (int)(interval[threadNumber][1]);
		threadNumber++;
		for (int i = begin; i <= end; i++) if (prime(i) != 0) numPrimes++;
		int primes[] = new int[numPrimes];
		System.out.print("Thread " + threadNumber + " found: ");
		for (int j = begin; j <= end; j++) if (prime(j) != 0) System.out.print(prime(j) + " ");
		System.out.println();

	}

}

public class Threads extends Prime {
	
	public static void main(String [] args){

			Scanner in = new Scanner(System.in);

			System.out.print("Enter the max numbers: ");
			n = in.nextInt();
		
			System.out.print("Enter the number of threads, <= " + MAXTHREADS + ": ");
			numThreads = in.nextInt();

			size = n / numThreads;
			start = 0; // intialize the starting position to 0
			threadNumber = 0;
			
			Thread thrd [] = new Thread[numThreads];
			for (int i = 0; i < numThreads; i++){
				interval[i][0] = start;
				interval[i][1] = start + size;
				start += size;
				thrd[i] = new Thread(new Prime());
				thrd[i].start();
			}

			try {
				for (int i = 0; i < numThreads; i++) thrd[i].join();

			} catch(InterruptedException ie){}

		
	}


}
