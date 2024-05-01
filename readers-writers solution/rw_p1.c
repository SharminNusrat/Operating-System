//First readers-writers problem (readers-preference)

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t resource;
sem_t rmutex;
int readcount = 0;
int count = 1;

void* reader (void* id) {
	
	
	int rid = *(int*)id;
	
	while(1) {
		sleep(1);
		sem_wait(&rmutex);
		readcount++;
		if(readcount == 1) {
			sem_wait(&resource);
		}
		sem_post(&rmutex);
	
		printf("Reader [%d] read the value = %d\n", rid, count);
	
		sem_wait(&rmutex);
		readcount--;
		if(readcount == 0) {
			sem_post(&resource);
		}
		sem_post(&rmutex);
	}
}

void* writer (void* id) {
	
	
	int wid = *(int*)id;
	
	while(1){
		sleep(1);
		sem_wait(&resource);
		count++;
		printf("Writer [%d] updated the value to %d\n", wid, count);
		sem_post(&resource);
	}
}

int main (int argc, char* argv[]) {

	pthread_t rd[10], wr[5];
	sem_init(&resource, 0, 1);
	sem_init(&rmutex, 0, 1);
	
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	
	for(int i=0; i<10; i++) {
		pthread_create(&rd[i], NULL, reader, (void*)&a[i]);
	}
	
	for(int i=0; i<5; i++) {
		pthread_create(&wr[i], NULL, writer, (void*)&a[i]);
	}
	
	for(int i=0; i<10; i++) {
		pthread_join(rd[i], NULL);
	}
	
	for(int i=0; i<5; i++) {
		pthread_join(wr[i], NULL);
	}
	
	sem_destroy(&rmutex);
	sem_destroy(&resource);
	
	return 0;
}
