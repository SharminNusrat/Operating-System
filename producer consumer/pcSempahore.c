#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t semEmpty;
sem_t semFull;

int buffer[10];
int count = 0;
pthread_mutex_t mutexBuffer;

void* producer(void* args) {
	
	while(1) {
		int x = rand() % 100;
		sleep(1);
		
		sem_wait(&semEmpty);
		pthread_mutex_lock(&mutexBuffer);
		buffer[count] = x;
		count++;
		sem_post(&semFull);
		pthread_mutex_unlock(&mutexBuffer);
	}
}

void* consumer(void* args) {

	while(1) {
		int y;
		
		sem_wait(&semFull);
		pthread_mutex_lock(&mutexBuffer);
		y = buffer[count-1];
		count--;
		sem_post(&semEmpty);
		pthread_mutex_unlock(&mutexBuffer);
	
		printf("Got %d\n", y);
		sleep(1);
	}
}	

int main (int argc, char* argv[]) {
	srand(time(NULL));
	pthread_t th[THREAD_NUM];
	pthread_mutex_init(&mutexBuffer, NULL);
	sem_init(&semEmpty, 0, 10);
	sem_init(&semFull, 0, 0);
	
	for(int i=0; i<THREAD_NUM; i++) {
		if(i % 2 == 0) 
			pthread_create(&th[i], NULL, &producer, NULL);
		else
			pthread_create(&th[i], NULL, &consumer, NULL); 
	}
	for(int i=0; i<THREAD_NUM; i++) {
		pthread_join(th[i], NULL);
	}
	pthread_mutex_destroy(&mutexBuffer);
	sem_destroy(&semEmpty);
	sem_destroy(&semFull);
	
	return 0;
}
