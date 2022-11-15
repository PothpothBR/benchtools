#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string.h>
#include "benchmark.h"

static PyObject* BTAddBenchFunction(PyObject* self, PyObject* args){
    PyObject *f;
    const char* s;
    int i;

    if (!PyArg_ParseTuple(args, "Osi", &f, &s, &i)) return NULL;

    char* ss = PyMem_Calloc(sizeof(char), strlen(s));
    strcpy(ss, s); // TODO: verificar se já foi corrigido

    Py_INCREF(f);
    addBenchmarkFunction(f, ss, i);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* BTBenchmarkFunctions(PyObject* self, PyObject* args){

    startBenchmark();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* BTFreeFunctionTable(PyObject* self, PyObject* args){

    freeBenchmark();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef BenchToolsMethods[] = {
    {"set_bench", BTAddBenchFunction, METH_VARARGS, "Adiciona um callable para executar na rodada de benchmark"},
    {"bench_round", BTBenchmarkFunctions, METH_NOARGS, "executa a rodada de benchmark"},
    {"clear_round", BTFreeFunctionTable, METH_NOARGS, "limpa a rodada de benchmark"},
    {NULL}
};

static struct PyModuleDef BenchTools = {
    PyModuleDef_HEAD_INIT,
    "benchtools",
    NULL,
    -1,
    BenchToolsMethods
};

PyMODINIT_FUNC PyInit_benchtools(void) {
    return PyModule_Create(&BenchTools);
}