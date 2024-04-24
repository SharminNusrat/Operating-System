#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUM 16

sem_t semaphore;

void* routine(void* args) {
	printf("%d waiting in the login queue\n", *(int*)args);
	sem_wait(&semaphore);
	printf("%d logged in\n", *(int*)args);
	sleep(rand() % 5 + 1 );
	printf("%d logged out\n", *(int*)args);
	sem_post(&semaphore);
	free(args);
}

int main (int argc, char* argv[]) {
	pthread_t th[THREAD_NUM];
	sem_init(&semaphore, 0, 4);
	for(int i=0; i<THREAD_NUM; i++) {
		int* a = malloc(sizeof(int));
		*a = i;
		if(pthread_create(&th[i], NULL, &routine, a) != 0) {
			perror("Failed to create thread\n");
		}
	}
	
	for(int i=0; i<THREAD_NUM; i++) {
		if(pthread_join(th[i], NULL) != 0) {
			perror("Failed to join thread\n");
		}
	}
	
	return 0;
} 
