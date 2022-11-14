#ifndef BENCHMARK_SOURCE_INCLUDED
#define BENCHMARK_SOURCE_INCLUDED

#include <Python.h>
#include "benchmark.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// TODO list * -
// * Geração de tabela dinamica
// * Benchmarks medidos por tempo e ou clock
// * Salvar resultado para arquivo
// * Benchmarks de comparação
//    * 1x1
//    * 1xN
//    * NxN

void addBenchmarkFunction(PyObject* function, const char* name, int average){
	if (benchmarkTable.buffered >= benchmarkTable.size) {
		benchmarkTable.size += FUNCTION_STACK_INCREASE;
		benchmarkTable.function = (PyObject*)PyMem_Realloc(
			benchmarkTable.function,
			benchmarkTable.size
		);
		benchmarkTable.name = (PyObject*)PyMem_Realloc(
			benchmarkTable.name,
			benchmarkTable.size
		);
		benchmarkTable.average = (PyObject*)PyMem_Realloc(
			benchmarkTable.average,
			benchmarkTable.size
		);
	}
	benchmarkTable.name[benchmarkTable.buffered] = name;
	benchmarkTable.function[benchmarkTable.buffered] = function;
	benchmarkTable.average[benchmarkTable.buffered++] = average;
}

void startBenchmark() {
	long counter = clock(),
		 minimum = LONG_MAX,
		 maximum = 0,
		 average = 0,
		 total = 0;
	PyObject* function;

	printf("\nIniciando rodada de benchmark para %i execucoes\n", benchmarkTable.buffered);

	printf("    #-----------------------------------------------------#\n");
	printf("    |        nome       |  maximo  |  minimo  |   media   |\n");
	printf("    |-----------------------------------------------------|\n");
	for (unsigned int i = 0; i < benchmarkTable.buffered; i++) {
		function = benchmarkTable.function[i];
		average = 0;
		minimum = LONG_MAX;
		maximum = 0;
		for (unsigned int e = 0; e < benchmarkTable.average[i]; e++) {
			printf("\r    [%i/%i] [%s... [%i/%i]]",  i + 1,  benchmarkTable.buffered, benchmarkTable.name[i], e+1, benchmarkTable.average[i]);
			
			counter = clock();
			PyObject_CallObject(function, NULL);
			counter = clock() - counter;

			average += counter;
			minimum = min(minimum, counter);
			maximum = max(maximum, counter);
		}

		average /= benchmarkTable.average[i];
		total += average;

		printf("\r    |%-19s|%10i|%10i|%11i|   \n", benchmarkTable.name[i], average, minimum, maximum);
	}
	printf("    |-----------------------------------------------------|\n");
	printf("    | total | %-44i|\n", total);
	printf("    #-----------------------------------------------------#\n");
	printf("Finalizando rodada de benchmark\n");
}

void freeBenchmark() {
	for (int i = 0; i < benchmarkTable.buffered; i++) {
		PyMem_Free(benchmarkTable.name[i]);
		Py_DECREF(benchmarkTable.function[i]);
	}
	
	PyMem_Free(benchmarkTable.name);
	Py_DECREF(benchmarkTable.function);
	PyMem_Free(benchmarkTable.average);
	benchmarkTable.size = 0;
	benchmarkTable.buffered = 0;
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BENCHMARK_SOURCE_INCLUDED
