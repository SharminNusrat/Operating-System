#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void* roll_dice() {
	int value = 1 + (rand() % 6);
	int* result = malloc(sizeof(int));
	*result = value;
 	//printf("%d\n",value);
 	printf("Thread result: %p\n", result);
 	return (void*) result;
}

int main (int argc, char* argv[]) {
	int* res;
	srand(time(NULL));
	pthread_t th;
	if(pthread_create(&th, NULL, roll_dice, NULL) != 0) {
		return 1;
	}
	if(pthread_join(th, (void**) &res) != 0) {
		return 2;
	}
	printf("Main result: %p\n", res);
	printf("Result: %d\n", *res);
	free(res);
	
	return 0;
}
