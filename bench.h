/*
bench.h
CINVESTAV-IPN
A.H.Sánchez A.Faz
Public domain.
*/

#ifndef BENCH_H
 #define BENCH_H

/**
 * Runs a new benchmark.
 * @param[in] LABEL			- the label for this benchmark.
 */
#define BENCH_BEGIN(LABEL, BENCH)										\
	bench_reset();														\
	label_print(LABEL);													\
	for (i = 0; i < BENCH; i++)	{										\

/**
 * Prints the mean timing of each execution in nanoseconds.
 */
#define BENCH_END(BENCH1,BENCH2)												\
	}																	\
	bench_compute(BENCH2 * BENCH1);										\
	bench_print()														\

/**
 * Measures the time of one execution and adds it to the benchmark total.
 *
 * @param[in] FUNCTION		- the function executed.
 */
#define BENCH_ADD(FUNCTION, BENCH)										\
	FUNCTION;															\
	bench_before();														\
	for (j = 0; j < BENCH; j++) {										\
		FUNCTION;														\
	}																	\
	bench_after();														\

/*====================================================================*/
/* Function prototypes                                                */
/*====================================================================*/
void label_print(char *s);
void bench_reset(void);
void bench_before(void);
void bench_after(void);
void bench_compute(int benches);
void bench_print(void);

#endif
