// HPCSE I: numerical integration: data structure pass as single argument to work() - code is ready for threads!
#include <stdio.h>
#include <math.h>
#include "timer.h"

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


//void work(double a, double dx, unsigned long begin, unsigned long end, double *S)
void work(arg_t *arg)
{
	double a = arg->a;
	double dx = arg->dx;
	unsigned long begin = arg->begin;
	unsigned long end = arg->end;
	double *S = arg->S;

	*S = 0;
	for (unsigned long i = begin; i < end; i++) {
		double xi = a + (i + 0.5)*dx;
		*S += f(xi);
	}
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

	arg_t arg1, arg2;
	arg1.a = a; arg1.dx = dx; arg1.begin = 0; arg1.end = n/2; arg1.S = &S1;
	arg2.a = a; arg2.dx = dx; arg2.begin = n/2; arg2.end = n; arg2.S = &S2;
	
	work(&arg1);
	work(&arg2);

	S = S1+S2;

	S *= dx;
	double t1 = get_wtime();

	printf("Time=%lf seconds, Result=%.8f\n", t1-t0, S);

	return 0; 
}
