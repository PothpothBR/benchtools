#ifndef BENCHMARK_HEADER_INCLUDED
#define BENCHMARK_HEADER_INCLUDED

// initial function stack size and stack increase amount
#ifndef FUNCTION_STACK_INCREASE
#define FUNCTION_STACK_INCREASE 100
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// for OS compatbility
#ifndef min
#define min(a, b) (a < b)? a : b
#endif

// for OS compatbility
#ifndef max
#define max(a, b) (a > b)? a : b
#endif

void addBenchmarkFunction(PyObject*, const char*, int);
void startBenchmark(char log);
void freeBenchmark();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // BENCHMARK_HEADER_INCLUDED