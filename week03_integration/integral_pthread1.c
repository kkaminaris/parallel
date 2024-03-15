// HPCSE I: numerical integration: moving loop to a separate work() function 
#include <stdio.h>
#include <math.h>
#include "timer.h"

double f(double x)
{
	return log(x)*sqrt(x);
}

double work(double a, double dx, unsigned long n)
{
	double S = 0;
	for (unsigned long i = 0; i < n; i++) {
		double xi = a + (i + 0.5)*dx;
		S += f(xi);
	}

	return S;
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

	S = work(a, dx, n);

	S *= dx;
	double t1 = get_wtime();

	printf("Time=%lf seconds, Result=%.8f\n", t1-t0, S);

	return 0; 
}
