/*
bench.c
CINVESTAV-IPN
A.H.Sánchez
Public domain.
*/

#include <stdio.h>
#include <time.h>
#include "bench.h"
#ifdef MODULE_CPUCYCLES
#include "cpucycles.h"
#endif

#ifdef MODULE_CPUCYCLES
unsigned long long before, after, total;
#else
static double  before, after, total;
#endif


char  szLogThis[500];

static double
now_ms(void)
{
    struct timespec res;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &res);
    return 1000.0*res.tv_sec + (double)res.tv_nsec/1e6;
}

void label_print(char *s){
	 sprintf(szLogThis, "%s", s);logC();
}

void bench_reset() {
	total = 0;
}

void bench_before() {
#ifdef MODULE_CPUCYCLES
	before= cpucycles();
#else
	before = now_ms();
#endif
}

void bench_after() {
	double result;
#ifdef MODULE_CPUCYCLES
	after = cpucycles();
#else
	after = now_ms();
#endif
	result = (after - before);
	total += result;
}

void bench_compute(int benches) {
#ifdef MODULE_CPUCYCLES
	total = total / benches;
#else
	total = total*1000 / benches;
#endif
}

void bench_print() {
#ifdef MODULE_CPUCYCLES
	 sprintf(szLogThis, "O: %lld cc", total);logC();
#else
	 sprintf(szLogThis, "O: %g us", total);logC();
#endif
}

