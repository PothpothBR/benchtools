#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string.h>
#include "benchmark.h"

static PyObject* py_add_bench_function(PyObject* self, PyObject* args){
    PyObject *f;
    const char* s;
    int i;

    if (!PyArg_ParseTuple(args, "Osi", &f, &s, &i)) return NULL;

    char* ss = PyMem_Calloc(sizeof(char), strlen(s));
    strcpy(ss, s);

    Py_INCREF(f);
    addBenchmarkFunction(f, ss, i);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* py_benchmark_functions(PyObject* self, PyObject* args){

    startBenchmark();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* py_free_functions(PyObject* self, PyObject* args){

    freeBenchmark();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef BenchtoolsMethods[] = {
    {"set_bench", py_add_bench_function, METH_VARARGS, "Adiciona um callable para executar na rodada de benchmark"},
    {"bench_round", py_benchmark_functions, METH_NOARGS, "executa a rodada de benchmark"},
    {"clear_round", py_free_functions, METH_NOARGS, "executa a rodada de benchmark"},
    {NULL}
};

static struct PyModuleDef benchtools = {
    PyModuleDef_HEAD_INIT,
    "benchtools",
    NULL,
    -1,
    BenchtoolsMethods
};

PyMODINIT_FUNC PyInit_benchtools(void) {
    return PyModule_Create(&benchtools);
}