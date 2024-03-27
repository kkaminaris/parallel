// numerical integration / sequential code
#include "timer.h"
#include <math.h>
#include <pthread.h>
#include <stdio.h>

double f(double x) {
    return log(x) * sqrt(x);
}

#define NUM_THREADS 3
pthread_t thread[NUM_THREADS];
pthread_mutex_t Mutex;
double a = 1.0;
double b = 4.0;
unsigned long const n = 1e9;
double dx;
double S = 0.0;

void *riemann(void *arg) {
    double start;
    double xi, sum = 0.0;

    start = (long)(*(int *)arg);

    for (unsigned long i = start; i < n; i += NUM_THREADS) {
        xi = a + (i + 0.5) * dx;
        sum += f(xi);
    }

    pthread_mutex_lock(&Mutex);
    S += sum;
    pthread_mutex_unlock(&Mutex);

    return 0;
}

// WolframAlpha: integral_1^4 log(x) sqrt(x) dx = 4/9 (4 log(64)-7)
// ~~ 4.28245881486164
int main(int argc, char *argv[]) {

    dx = (b - a) / n;

    int Arg[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
        Arg[i] = i;

    pthread_mutex_init(&Mutex, NULL);

    double t0 = get_wtime();

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&thread[i], NULL, riemann, &Arg[i]);

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(thread[i], NULL);

    S *= dx;

    double t1 = get_wtime();

    printf("Time=%lf seconds, Result=%.8f\n", t1 - t0, S);

    return 0;
}
