/*

	Author: Colby Garland ID# 5034957
	Assignment 2, Java threads/semaphores
	Purpose: Using java's built in threads and semaphore classes, implement the reader/writer problem 
		 favouring readers

*/

import java.io.*;
import java.util.concurrent.Semaphore;



class Reader extends Thread {
	private Semaphore mutex, wsem;
	static int readCount;
	private int id;
	private PrintStream pr;

	public Reader(Semaphore mutex, Semaphore wsem, int id, PrintStream pr){
		this.mutex = new Semaphore(1, true);
		this.wsem = new Semaphore(1, true);
		this.pr = pr;
		this.id = id;
	}

	public void run(){
		pr.println("Reader " + id + " trying to get into CR");
		try {
		mutex.acquire();
		} catch (Exception ignored) {}
		readCount++;
		if (readCount == 1) {
			try {
				wsem.acquire();
			} catch (Exception ignored) {}
		}
		mutex.release();
		pr.println("Reader " + id + " is reading");
		try {
			sleep((long)(Math.random() * 1000));
		} catch (Exception ignored) {}		
		pr.println("Reader " + id + " is done reading");
		try {
			mutex.acquire();
		} catch (Exception ignored) {}		
		readCount--;
		if (readCount == 0) wsem.release();
		mutex.release();
	}
}

class Writer extends Thread {
	private Semaphore wsem;
	private int id;
	private PrintStream pr;

	public Writer (Semaphore wsem, int id, PrintStream pr){
		this.wsem = new Semaphore(1, true);
		this.id = id;
		this.pr = pr;
	}

	public void run(){
		pr.println("Writer " + id + " is trying to write");
		try {
			wsem.acquire();
		} catch (Exception ignored) {}		
		pr.println("Writer " + id + " is starting to write");
		try {
			sleep((long)(Math.random() * 1000));
		} catch (Exception ignored) {}		
		pr.println("Writer " + id + " is done writing");
		wsem.release();
	}
}

public class ReadWrite extends Object {

	public static void main(String args[]){
		int rn = 0;
		int wn = 0;
		Semaphore writeBlock = new Semaphore(1, true);
		Semaphore mutex = new Semaphore(1, true);
		final int MAX = 10; // max number of threads

		for (int i = 0; i < MAX; i++){
			if (i % 2 == 1)
				new Reader(mutex, writeBlock, rn++, System.out).start();
			else new Writer(writeBlock, wn++, System.out).start();

		}
	}
}
