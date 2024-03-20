// Hello world from a POSIX thread
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int x = 10;

void *work(void *arg)
{
	pthread_t me = pthread_self();
	printf("Hello world from thread %lx!\n", (long)me);
    x = 20;
    printf("i=%lx\n", (long)arg);
    printf("Goodbye from thread\n");

	return NULL;
}

int main(int argc, char **argv)
{
	long i = 1;
	pthread_t thread;

	printf("Hello world from primary thread %lx!\n", (long)pthread_self());

	pthread_create(&thread, NULL, work,(void *) i);
    printf("Main: waiting...\n");
    sleep(2);
    x = 30;
	pthread_join(thread, NULL);

	printf("Child thread ended, exiting!\n");
    printf("x=%d\n", x);

	return 0;
}
