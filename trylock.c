#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

//chefs = threads
//stove = shared data (+mutex)

pthread_mutex_t stoveMutexes[4];
int stoveFuel[4] = {100, 100, 100, 100};

void* routine(void* arg) {
	for(int i=0; i<4; i++) {
		if(pthread_mutex_trylock(&stoveMutexes[i]) == 0) {
			int fuelNeeded = (rand() % 30);
			if(stoveFuel[i] - fuelNeeded < 0) {
				printf("No more fuel... going home\n");
			}
			else {
				stoveFuel[i] -= fuelNeeded;
				usleep(500000);
				printf("Fuel left %d\n", stoveFuel[i]);
			}
			pthread_mutex_unlock(&stoveMutexes[i]);	
			break;
		}
		else {
			if(i == 3) {
				printf("No stove available yet, waiting....\n");
				usleep(300000);
				i = 0;
			}
		}
	}
}

int main (int argc, char* argv[]) {
	srand(time(NULL));
	pthread_t th[10];
	for(int i=0; i<4; i++) {
		pthread_mutex_init(&stoveMutexes[i], NULL);
	}
	for(int i=0; i<10; i++) {
		if(pthread_create(&th[i], NULL, &routine, NULL) != 0) {
			perror("Failed to create thread");
		}
	}
	
	for(int i=0; i<10; i++) {
		if(pthread_join(th[i], NULL) != 0) {
			perror("Failed to join thread");
		}
	}
	for(int i=0; i<4; i++) {
		pthread_mutex_destroy(&stoveMutexes[i]);
	}
	
	return 0;
}
