// Spawning 4 threads
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "timer.c"

// int n = 1000;
// int p = 4;
// int chunk = n/p; //250
//
// int id; 0,1,2,3
//
// int start = id*chucnk;
// int end = start + chunk;
//
// id = 0 -> start = 0, end = 250
// id = 1 -> start = 250, end = 500

void *func(void *arg)
{
	long me = *(long *)arg;
	printf("Hello world from thread %lx!\n", (long)me);

	sleep(me);
    printf("Thread %lx is exiting!\n", (long)me);
	return NULL;
}

int main(int argc, char * argv[])
{
	pthread_t id[4];
    long tmp[4];

    double t0 = get_wtime();
	for (long i = 0; i < 4; i++)   {
        tmp[i] = i;
		pthread_create(&id[i], NULL, func, (void *) &tmp[i]);
	}

	for (long i = 0; i < 4; i++)   {
		pthread_join(id[i], NULL);
	}
    double t1 = get_wtime();
    printf("elapsed time=%lf s\n", t1-t0);

	return 0;
}
