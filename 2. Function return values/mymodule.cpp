#define PY_SSIZE_T_CLEAN
#include <Python.h>

/* your standardlib includes */
// #include <string>
#include <vector>

/* your other src file includes */
// #include "mysrcfile.hpp"

/* functions */

PyObject* retNone(PyObject* self, PyObject* args) {
	return Py_BuildValue("");	// this is recommended
	// or
    Py_RETURN_NONE;
    // or
    return Py_None;
}

PyObject* retBool(PyObject* self, PyObject* args) {
	// Py_BuildValue does not work
	Py_RETURN_TRUE;	// Py_RETURN_FALSE
	// or
	return Py_True;	// Py_False
}

PyObject* retInt(PyObject* self, PyObject* args) {
	return Py_BuildValue("i", 123);
	// or
	return PyLong_FromLong(123);
}

PyObject* retFloat(PyObject* self, PyObject* args) {
	return Py_BuildValue("d", 123.456);
	// or
	return PyFloat_FromDouble(123.456);
}

PyObject* retString(PyObject* self, PyObject* args) {
	return Py_BuildValue("s", "hello");
	// or
	return PyUnicode_FromString("hello");
}

PyObject* retTuple(PyObject* self, PyObject* args) {
	return Py_BuildValue("(ii)", 123, 456);
	// or
	// if there are multiple values it automatically becomes a tuple, no () needed
	return Py_BuildValue("ii", 123, 456);	
	// for tuples of other types replace i with wanted character
}

PyObject* retMixedTuple(PyObject* self, PyObject* args) {
	// tuples of different types are also possible
	return Py_BuildValue("is", 123, "hello");
}

PyObject* ret2DTuple(PyObject* self, PyObject* args) {
	return Py_BuildValue("((ii)(ii))", 123, 456, 123, 456);
	// or
	return Py_BuildValue("(ii)(ii)", 123, 456, 123, 456);
}

PyObject* retTupleOfVarSize(PyObject* self, PyObject* args) {
	std::vector<long> v {1, 2, 3, 4, 5, 6};
	PyObject* tuple = PyTuple_New(v.size());	// create a new tuple, size is important
	unsigned int index = 0;
	for (auto& elem : v) {
		PyObject* obj = PyLong_FromLong(elem);	// can be inlined
		if (PyTuple_SetItem(tuple, index++, obj) == -1)	// set item at each index
			return NULL;	// indexerror
	}
	return tuple;
}

PyObject* ret2DTupleOfVarSize(PyObject* self, PyObject* args) {
	std::vector<std::vector<long>> v {{1, 2, 3, 4},
									  {5, 6, 7},
									  {8, 9}};
	PyObject* tuple = PyTuple_New(v.size());	// create a new tuple, size is important
	unsigned int index = 0;
	for (auto& vec : v) {
		PyObject* tup = PyTuple_New(vec.size());	// create a new tuple, size is important
		unsigned int jndex = 0;
		for (auto& elem : vec) {
			PyObject* obj = PyLong_FromLong(elem);	// can be inlined
			if (PyTuple_SetItem(tup, jndex++, obj) == -1)	// set item at each index
				return NULL;	// indexerror
		}

		if (PyTuple_SetItem(tuple, index++, tup) == -1)	// set item at each index
			return NULL;	// indexerror
	}
	return tuple;
}

PyObject* retList(PyObject* self, PyObject* args) {
	return Py_BuildValue("[ii]", 123, 456);
	// for lists of Var types replace i with wanted character
	
	// lists of different types are also possible
	return Py_BuildValue("[is]", 123, "hello");
}

PyObject* ret2DList(PyObject* self, PyObject* args) {
	return Py_BuildValue("[[ii][ii]]", 123, 456, 123, 456);
}

PyObject* retListOfVarSize(PyObject* self, PyObject* args) {
	std::vector<long> v {1, 2, 3, 4, 5, 6};
	PyObject* list = PyList_New(0);		// create new list, size is not important, just use 0
	for (auto& elem : v) {
		PyObject* obj = PyLong_FromLong(elem);	// can be inlined
		if (PyList_Append(list, obj) == -1)	// append item to list
			return NULL;	// some error
	}
	return list;
}

PyObject* ret2DListOfVarSize(PyObject* self, PyObject* args){
	std::vector<std::vector<long>> v {{1, 2, 3, 4},
									  {5, 6, 7},
									  {8, 9}};
	PyObject* list = PyList_New(0);		// create new list, size is not important, just use 0
	for (auto& vec : v) {
		PyObject* ls = PyList_New(0);	// create new list, size is not important, just use 0
		for (auto& elem : vec) {
			PyObject* obj = PyLong_FromLong(elem);	// can be inlined
			if (PyList_Append(ls, obj) == -1)	// append item to list
				return NULL;	// some error
		}

		if (PyList_Append(list, ls) == -1)	// append item to list
			return NULL;	// some error
	}
	return list;
}

/* method definitions */
static PyMethodDef mymoduleMethods[] = {	/* name of your method def */
    {"retNone", retNone, METH_VARARGS, "."},
	{"retInt", retInt, METH_VARARGS, "."},
	{"retBool", retBool, METH_VARARGS, "."},
	{"retFloat", retFloat, METH_VARARGS, "."},
	{"retString", retString, METH_VARARGS, "."},
	{"retTuple", retTuple, METH_VARARGS, "."},
	{"retMixedTuple", retMixedTuple, METH_VARARGS, "."},
	{"ret2DTuple", ret2DTuple, METH_VARARGS, "."},
	{"retTupleOfVarSize", retTupleOfVarSize, METH_VARARGS, "."},
	{"ret2DTupleOfVarSize", ret2DTupleOfVarSize, METH_VARARGS, "."},
	{"retList", retList, METH_VARARGS, "."},
	{"ret2DList", ret2DList, METH_VARARGS, "."},
	{"retListOfVarSize", retListOfVarSize, METH_VARARGS, "."},
	{"ret2DListOfVarSize", ret2DListOfVarSize, METH_VARARGS, "."},
	{NULL, NULL, 0, NULL}	/* Sentinel */
};

/* module definition */
static struct PyModuleDef mymoduledef = {
	PyModuleDef_HEAD_INIT,
	"myModule",						/* name of module (same as setup.py) */
	"some module documentation",	/*	module documentation */
	-1,
	mymoduleMethods					/* name of your method def */
};

/* mod init */
PyMODINIT_FUNC
PyInit_myModule(void) { 		/* name of module (same as setup.py) after PyInit_ */
	PyObject* m = PyModule_Create(&mymoduledef);
	if (m == NULL)
		return NULL;
	return m;
}