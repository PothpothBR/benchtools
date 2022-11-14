#ifndef BENCHMARK_HEADER_INCLUDED
#define BENCHMARK_HEADER_INCLUDED

#ifndef FUNCTION_STACK_INCREASE
#define FUNCTION_STACK_INCREASE 100
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifndef min
#define min(a, b) (a < b)? a : b
#endif

#ifndef max
#define max(a, b) (a > b)? a : b
#endif

void addBenchmarkFunction(PyObject*, const char*, int);
void startBenchmark();
void freeBenchmark();
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BENCHMARK_HEADER_INCLUDED