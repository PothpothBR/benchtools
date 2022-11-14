#ifndef BENCHMARK_HEADER_INCLUDED
#define BENCHMARK_HEADER_INCLUDED

#ifndef FUNCTION_STACK_INCREASE
#define FUNCTION_STACK_INCREASE 100
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct _FunctionTable {
	PyObject** function;
	const char **name;
	int *average;
	unsigned buffered;
	unsigned size;
}FunctionTable;

static FunctionTable benchmarkTable = {0};

void addBenchmarkFunction(PyObject*, const char*, int);
void startBenchmark();
void freeBenchmark();
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BENCHMARK_HEADER_INCLUDED