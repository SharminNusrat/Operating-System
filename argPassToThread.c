/*
  Create 10 threads, each taking a unique prime from the 
  primes array and print it on the screen.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* param) {
	sleep(1);
	int* prime = (int*) param;
	printf("%d\n", *prime);
}

int main (int argc, char* argv[]) {
	pthread_t threads[10];
	
	for(int i=0; i<10; i++) {
		pthread_create(&threads[i], NULL, &routine, (void*) &primes[i]);
	}
	for(int i=0; i<10; i++) {
		pthread_join(threads[i], NULL);
	}
	
	return 0;
}
