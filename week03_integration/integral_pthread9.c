// HPCSE I: numerical integration: one spawned thread, local sum and single result updated by both threads
// Note: mutex to avoid race conditions
#include <stdio.h>
#include <math.h>
#include "timer.h"
#include <pthread.h>

double f(double x)
{
	return log(x)*sqrt(x);
}


typedef struct arg_s
{
	double a;
	double dx;
	double begin;
	double end;
	double *S;
} arg_t;


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *work(void *thread_arg)
{
	arg_t *arg = (arg_t *) thread_arg;
	double a = arg->a;
	double dx = arg->dx;
	unsigned long begin = arg->begin;
	unsigned long end = arg->end;
	double *S = arg->S;

	double local_S = 0;
	for (unsigned long i = begin; i < end; i++) {
		double xi = a + (i + 0.5)*dx;
		local_S += f(xi);
	}

	pthread_mutex_lock(&mutex);
	*S += local_S;
	pthread_mutex_unlock(&mutex);

	return NULL;
}


// WolframAlpha: integral_1^4 log(x) sqrt(x) dx = 4/9 (4 log(64)-7) ~~ 4.28245881486164
int main(int argc, char *argv[])
{
	double a = 1.0;
	double b = 4.0;
	unsigned long const n = 1e9;
	const double dx = (b-a)/n;

	double S = 0;

	double t0 = get_wtime();

	arg_t arg1, arg2;
	arg1.a = a; arg1.dx = dx; arg1.begin = 0; arg1.end = n/2; arg1.S = &S;
	arg2.a = a; arg2.dx = dx; arg2.begin = n/2; arg2.end = n; arg2.S = &S;

	pthread_t thr1;

	pthread_create(&thr1, NULL, work, (void *)&arg1);
	work(&arg2);

	pthread_join(thr1, NULL);

	S *= dx;
	double t1 = get_wtime();

	printf("Time=%lf seconds, Result=%.8f\n", t1-t0, S);

	return 0; 
}
