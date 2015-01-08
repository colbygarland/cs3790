/* 

	Author: Colby Garland ID# 5034957
	Assignment #2
	Purpose: Using pthreads, implement the reader/writer problem favouring readers.

*/

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX 10 // max number of threads

void *reader(void *); // doing the "reading"
void *writer(void *); // doing the "writing"

sem_t mutex, wsem;
long id[MAX];
int count, readCount, r;

void *reader(void * param){

   while(1){

	id[count] = (long)(param);

	r = rand() * 1;	

	printf("Reader %ld is trying to get into CR\n", id[count]);

	sem_wait(&mutex);
	readCount++;
	if (readCount == 1) sem_wait(&wsem);

	sem_post(&mutex);
	printf("Reader %ld is reading\n", id[count]);
	
	sleep(r);

	printf("Reader %ld is done writing\n", id[count]);
	sem_wait(&mutex);
	readCount--;
	
	if (readCount == 0) sem_post(&wsem);

	pthread_exit(0);
   }
}

void *writer(void * param){

   while(1){
	
	id[count] = (long)(param);
	r = rand();

	printf("Writer %ld is trying to write\n", id[count]);

	sem_wait(&wsem);

	printf("Writer %ld is starting to write\n", id[count]);
	sleep(r);
	
	printf("Writer %ld is done writing\n", id[count]);
	sem_post(&wsem);

	pthread_exit(0);

   }
}

int main(){

	srand(time(NULL));

	count = 0;
	sem_init(&mutex, 0, 1);
	sem_init(&wsem, 0, 1);

	pthread_t tid [MAX]; // the thread identifier 
	pthread_attr_t attr;

		
	
	int i;
	for (i = 0; i < MAX; i++){
		if (i % 2 == 1){
			pthread_attr_init(&attr);	
			pthread_create(&tid[i], NULL, reader, id);
		} else {
			pthread_attr_init(&attr);	
			pthread_create(&tid[i], NULL, writer, id);
		}
		count++;
	}

	//for (i = 0; i < MAX; i++) pthread_join(tid[i],NULL); // joining the threads


}
