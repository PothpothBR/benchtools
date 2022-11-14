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

// TODO list * -
// * Geração de tabela dinamica
// * Benchmarks medidos por tempo e ou clock
// * ao lado do tempo sinalizar o melhor tempo / a diferenca de tempo se, em comparação
// * Salvar resultado para arquivo
// * Benchmarks de comparação
//    * 1x1
//    * 1xN
//    * NxN
//    * #xN (aonde # é o melhor resultado obtido)

typedef struct _FunctionTable {
	PyObject** function;
	const char **name;
	int *average;
	unsigned buffered;
	unsigned size;
}FunctionTable;

static FunctionTable BenchTable = {0};

void addBenchmarkFunction(PyObject* function, const char* name, int average){
	if (BenchTable.buffered >= BenchTable.size) {
		BenchTable.size += FUNCTION_STACK_INCREASE;
		BenchTable.function = (PyObject**)PyMem_Realloc(
			BenchTable.function,
			BenchTable.size
		);
		BenchTable.name = (const char**)PyMem_Realloc(
			BenchTable.name,
			BenchTable.size
		);
		BenchTable.average = (int*)PyMem_Realloc(
			BenchTable.average,
			BenchTable.size
		);
	}
	BenchTable.name[BenchTable.buffered] = name;
	BenchTable.function[BenchTable.buffered] = function;
	BenchTable.average[BenchTable.buffered++] = average;
}

void startBenchmark() {
	long counter = clock(),
		 minimum = LONG_MAX,
		 maximum = 0,
		 average = 0,
		 total = 0;
	PyObject* function;

	printf("\nIniciando rodada de benchmark para %i execucoes\n", BenchTable.buffered);

	printf("    #-----------------------------------------------------#\n");
	printf("    |        nome       |  maximo  |  minimo  |   media   |\n");
	printf("    |-----------------------------------------------------|\n");
	for (unsigned int i = 0; i < BenchTable.buffered; i++) {
		function = BenchTable.function[i];
		average = 0;
		minimum = LONG_MAX;
		maximum = 0;
		for (int e = 0; e < BenchTable.average[i]; e++) {
			printf("\r    [%i/%i] [%s... [%i/%i]]",  i + 1,  BenchTable.buffered, BenchTable.name[i], e+1, BenchTable.average[i]);
			
			counter = clock();
			PyObject_CallObject(function, NULL);
			counter = clock() - counter;

			average += counter;
			minimum = min(minimum, counter);
			maximum = max(maximum, counter);
		}

		average /= BenchTable.average[i];
		total += average;

		printf("\r    |%-19s|%10li|%10li|%11li|   \n", BenchTable.name[i], average, minimum, maximum);
	}
	printf("    |-----------------------------------------------------|\n");
	printf("    | total | %-44li|\n", total);
	printf("    #-----------------------------------------------------#\n");
	printf("Finalizando rodada de benchmark\n");
}

void freeBenchmark() {
	for (unsigned int i = 0; i < BenchTable.buffered; i++) {
		PyMem_Free(BenchTable.name[i]);
		Py_DECREF(BenchTable.function[i]);
	}
	
	PyMem_Free(BenchTable.name);
	Py_DECREF(BenchTable.function);
	PyMem_Free(BenchTable.average);
	BenchTable.size = 0;
	BenchTable.buffered = 0;
}

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BENCHMARK_SOURCE_INCLUDED
