#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

float avg;
int min;
int max;

struct ThreadParams {
	int argc;
	char **argv;
};

void* average(void* param);
void* minimum(void* param);
void* maximum(void* param);

int main(int argc, char* argv[]) {
	
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;
	struct ThreadParams params;
	
	if (argc < 2) {
		fprintf(stderr,"usage: a.out <integer> <integer> ...\n");
		return -1;
	}
	
	params.argc = argc;
	params.argv = argv;
	
	pthread_create(&thread1, NULL, average, &params);
	pthread_create(&thread2, NULL, minimum, &params);
	pthread_create(&thread3, NULL, maximum, &params);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
		
	printf("The average value is %.2f\n", avg);
	printf("The minimum value is %d\n", min);
	printf("The maximum value is %d\n", max);	
	
	return 0;
} 

void* average(void* param) {
	struct ThreadParams *params = (struct ThreadParams *)param;
	avg = 0;
	
	for(int i=1; i< params->argc; i++) {
		avg += atoi(params -> argv[i]);
	}
	
	avg /= (params->argc -1);
	
	pthread_exit(0);
}

void* minimum(void* param) {
	struct ThreadParams *params = (struct ThreadParams *)param;
	min = INT_MAX;
	
	for(int i=1; i< params->argc; i++) {
		if(atoi(params->argv[i]) < min) {
			min = atoi(params->argv[i]);
		}
	}
	
	pthread_exit(0);
}

void* maximum(void* param) {
	struct ThreadParams *params = (struct ThreadParams *)param;
	max = INT_MIN;
	
	for(int i=1; i< params->argc; i++) {
		if(atoi(params->argv[i]) > max) {
			max = atoi(params->argv[i]);
		}
	}
	
	pthread_exit(0);
}