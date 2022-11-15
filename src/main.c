#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string.h>
#include "benchmark.h"

static PyObject *NotCallableError;

static PyObject* BTAddBenchFunction(PyObject* self, PyObject* args){
    PyObject *f;
    const char* s;
    int i;

    if (!PyArg_ParseTuple(args, "Osi", &f, &s, &i)) return NULL;

    if (PyCallable_Check(f)){
        Py_INCREF(f);
        addBenchmarkFunction(f, s, i);
        Py_INCREF(Py_None);
        return Py_None;
    }
    
    PyErr_SetString(NotCallableError, "Your object not is callable!");
    return NULL;
}

static PyObject* BTBenchmarkFunctions(PyObject* self, PyObject* args){
    char l = 0;

    if (!PyArg_ParseTuple(args, "|p", &l)) return NULL;

    startBenchmark(l);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* BTFreeFunctionTable(PyObject* self, PyObject* args){

    freeBenchmark();

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef BenchToolsMethods[] = {
    {"set_bench", BTAddBenchFunction, METH_VARARGS, "Add a callable to run in the benchmark round"},
    {"bench_round", BTBenchmarkFunctions, METH_VARARGS, "Run the benchmark round"},
    {"clear_round", BTFreeFunctionTable, METH_NOARGS, "Clear the benchmark round"},
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

    PyObject* mod = PyModule_Create(&BenchTools);
    if (mod == NULL) return NULL;

    NotCallableError = PyErr_NewException("notcallable.error", NULL, NULL);
    Py_XINCREF(NotCallableError);

    if (PyModule_AddObject(mod, "error", NotCallableError) < 0) {
        Py_XDECREF(NotCallableError);
        Py_CLEAR(NotCallableError);
        Py_DECREF(mod);
        return NULL;
    }

    return mod;
}