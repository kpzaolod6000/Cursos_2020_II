#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include <pthread.h>

int global;
void *thr_func(void *arg);
int main(void)
{
	pthread_t tid;
	global = 20;
	printf("Thread principal: %d\n", global);
	pthread_create(&tid, NULL, thr_func, NULL);
	pthread_join(tid, NULL);
   //sleep(1);
	printf("Thread principal: %d\n", global);
	return 0;
}

void *thr_func(void *arg)
{
	global = 40;
	printf("Nova thread: %d\n", global);
   sleep(10);
   printf("END Nova thread\n");
	return NULL;
}

