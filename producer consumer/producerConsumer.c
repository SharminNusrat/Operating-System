#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include "buffer.h"

sem_t semFull;
sem_t semEmpty;
pthread_mutex_t mutex;

buffer_item buffer[BUFFER_SIZE];
int count = 0;

int insert_item(buffer_item item) {

	sem_wait(&semEmpty);
	pthread_mutex_lock(&mutex);
	
	if(count < BUFFER_SIZE) {
		buffer[count] = item;
		count++;
		sem_post(&semFull);
		pthread_mutex_unlock(&mutex);
		return 0;
	}
	else {
		pthread_mutex_unlock(&mutex);
		sem_post(&semEmpty);
		return -1;
	}
}

int remove_item(buffer_item *item) {
	
	sem_wait(&semFull);
	pthread_mutex_lock(&mutex);
	
	if(count > 0) {
		*item = buffer[count-1];
		count--;
		sem_post(&semEmpty);
		pthread_mutex_unlock(&mutex);
	}
	else {
		pthread_mutex_unlock(&mutex);
		sem_post(&semFull);
		return -1;
	}
}

void* producer(void* param) {
	buffer_item item;
	
	while(1) {
		sleep(1);
		item = rand();
		if(insert_item(item)) {
			fprintf(stderr,"Report error condition");
		}
		else {
			printf("Producer produced %d\n", item);	
		}
	}
}

void* consumer(void* param) {
	buffer_item item;
	
	while(1) {
		sleep(1);
		if(remove_item(&item)) {
			fprintf(stderr,"Report error condition");
		}
		else {
			printf("Consumer consumed %d\n", item);
		}
	}
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	
	if (argc < 4) {
		fprintf(stderr,"usage: a.out <integer> <integer> ...\n");
		return -1;
	}
	
	int sleepTime = atoi(argv[1]);
	int numProducer = atoi(argv[2]);
	int numConsumer = atoi(argv[3]);
	
	pthread_t producerTh[numProducer];
	pthread_t consumerTh[numConsumer];
	
	pthread_mutex_init(&mutex, NULL);
	sem_init(&semFull, 0, 0);
	sem_init(&semEmpty, 0, BUFFER_SIZE);
		
	for(int i=0; i<BUFFER_SIZE; i++) {
		buffer[i] = -1;
	}
	
	for(int i=0; i<numProducer; i++) {
		pthread_create(&producerTh[i], NULL, &producer, NULL);
	}
	
	for(int i=0; i<numConsumer; i++) {
		pthread_create(&consumerTh[i], NULL, &consumer, NULL);
	}
	
	sleep(sleepTime);
	
	pthread_mutex_destroy(&mutex);
	sem_destroy(&semFull);
	sem_destroy(&semEmpty);
	
	return 0;
}