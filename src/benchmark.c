#ifndef BENCHMARK_SOURCE_INCLUDED
#define BENCHMARK_SOURCE_INCLUDED

#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "benchmark.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct _FunctionTable {
	PyObject** function;  // function list
	const char **name;    // alias names
	int *average;         // average result list
	unsigned buffered;    // size of stack filled
	unsigned size;        // total stask size
}FunctionTable;

// StackTable
static FunctionTable BenchTable = {0};

// add a PyObject to stack
void addBenchmarkFunction(PyObject* function, const char* name, int average){
	if (BenchTable.buffered >= BenchTable.size) {
		BenchTable.size += FUNCTION_STACK_INCREASE;
		BenchTable.function = (PyObject**)realloc(
			BenchTable.function,
			BenchTable.size
		);
		BenchTable.name = (const char**)realloc(
			BenchTable.name,
			BenchTable.size
		);
		BenchTable.average = (int*)realloc(
			BenchTable.average,
			BenchTable.size
		);
	}
	BenchTable.name[BenchTable.buffered] = name;
	BenchTable.function[BenchTable.buffered] = function;
	BenchTable.average[BenchTable.buffered++] = average;
}

// try to call all functions in stack catching clock execution results
void startBenchmark(char log) {
	if (!BenchTable.buffered) return;

	long counter = clock(),
		 minimum = LONG_MAX,
		 maximum = 0,
		 average = 0,
		 best_average = LONG_MAX,
		 best_index = 0,
		 total = 0;

	PyObject* function;

	FILE *log_file = NULL;

	if (log) {
		log_file = fopen("benchmark.log.csv", "w");
		fprintf(log_file, ",nome,maximo,minimo,media\n");
	}

	printf("\n   #=====================#============#============#=============#\n");
	printf(  "  ||         nome        |   maximo   |   minimo   |    media    ||\n");
	printf(  "  ||---------------------|------------|------------|-------------||\n");

	for (unsigned int i = 0; i < BenchTable.buffered; i++) {
		if (!BenchTable.average[i]) continue;

		function = BenchTable.function[i];
		average = 0;
		minimum = LONG_MAX;
		maximum = 0;
		for (int e = 0; e < BenchTable.average[i]; e++) {
			printf("\r   Rodado [%i/%i] Executando \"%s\" Etapa [%i/%i]",  i + 1,  BenchTable.buffered, BenchTable.name[i], e+1, BenchTable.average[i]);
			
			counter = clock();
			PyObject_CallObject(function, NULL);
			counter = clock() - counter;

			average += counter;
			minimum = min(minimum, counter);
			maximum = max(maximum, counter);
		}
		average /= BenchTable.average[i];
		if (average < best_average) {
			best_average = average;
			best_index = i;
		}
		total += average;

		if (log) fprintf(log_file, "%i,\"%s\",%li,%li,%li\n", i, BenchTable.name[i], average, minimum, maximum);
		printf("\r  ||%-21s|%12li|%12li|%13li||   \n", BenchTable.name[i], average, minimum, maximum);
	}
	printf("   #===============================================#=============#\n");
	printf("   #=====================#============#========#=================#\n");
	printf("  ||       melhor        |    media   | rodado |      total      ||\n");
	printf("  ||---------------------|------------|--------|-----------------||\n");
	printf("  ||%-21s|%12li|%8li|%17li||\n", BenchTable.name[best_index], best_average, BenchTable.buffered, total);
	printf("   #=====================#============#========#=================#\n");

	if (log) fclose(log_file);
}

// Free the table, alow reuse the stack
void freeBenchmark() {
	for (unsigned int i = 0; i < BenchTable.buffered; i++) {
		Py_DECREF(BenchTable.name[i]);
		Py_DECREF(BenchTable.function[i]);
		BenchTable.name[i] = NULL;
		BenchTable.function[i] = NULL;
	}
	
	free(BenchTable.name);
	free(BenchTable.function);
	free(BenchTable.average);
	BenchTable.name = NULL;
	BenchTable.function = NULL;
	BenchTable.average = NULL;

	BenchTable.buffered = 0;
	BenchTable.size = 0;
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BENCHMARK_SOURCE_INCLUDED
