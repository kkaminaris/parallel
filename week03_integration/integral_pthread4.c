// HPCSE I: numerical integration: work() accepts the loop bounds as arguments
// Note: the result of work() is not returned but written to function argument that has been passed by reference (C pointer)
#include <stdio.h>
#include <math.h>
#include "timer.h"

double f(double x)
{
	return log(x)*sqrt(x);
}


void work(double a, double dx, unsigned long begin, unsigned long end, double *S)
{
	*S = 0;
	for (unsigned long i = begin; i < end; i++) {
		double xi = a + (i + 0.5)*dx;
		*S += f(xi);
	}

	return;
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

	double S1, S2;

	work(a, dx, 0, n/2, &S1);
	work(a, dx, n/2, n, &S2);

	S = S1+S2;

	S *= dx;
	double t1 = get_wtime();

	printf("Time=%lf seconds, Result=%.8f\n", t1-t0, S);

	return 0; 
}
