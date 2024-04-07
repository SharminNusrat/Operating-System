#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

int inCount;
int totCount;
int numThreads;

pthread_mutex_t mutex;


float genRanNum();
void* calc(void *threadId);

int main (int argc, char* argv[]) {
	
	float pi;
	inCount = 0;
	totCount = 10000670;
	numThreads = 10;
	pthread_t threads[numThreads];
	pthread_mutex_init(&mutex, NULL);
	
	for(long i=0; i<numThreads; i++) {
		pthread_create(&threads[i], NULL, calc, (void *)i);
	}
	
	for(int i=0; i<numThreads; i++) {
		pthread_join(threads[i], NULL);
	}
	
	pthread_mutex_destroy(&mutex);
	
	pi = 4.0 * ((float)inCount / (float)totCount);
	
	printf("Estimation of the pi value: %f\n",pi);
	
	return 0;
}

float genRanNum() {
	//srand( time(NULL) );
	int random = rand();
	float unit_random = random / (float) RAND_MAX;
	
	return unit_random;
}

void* calc(void *threadId) {
	
	long id = (long ) (threadId);
	int iterations = totCount / numThreads;
	
	for(int i=0; i<iterations; i++) {
		
		float x = genRanNum();
		float y = genRanNum();
		
		float result = sqrt((x*x) + (y*y));
		
		if(result <=1) {
			pthread_mutex_lock(&mutex);
			inCount++;
			pthread_mutex_unlock(&mutex);
		}
	}
	
	if(id == 0) {
		int remainingCount = totCount % numThreads;
		for(int i=0; i<remainingCount; i++) {
			float x = genRanNum();
			float y = genRanNum();
		
			float result = sqrt((x*x) + (y*y));
		
			if(result <=1) {
				pthread_mutex_lock(&mutex);
				inCount++;
				pthread_mutex_unlock(&mutex);
			}
		}
	}
	
	pthread_exit(0);
}