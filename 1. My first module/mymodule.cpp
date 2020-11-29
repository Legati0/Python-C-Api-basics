#define PY_SSIZE_T_CLEAN
#include <Python.h>

/* your standardlib includes */
// #include <string>

/* your other src file includes */
// #include "mysrcfile.hpp"

/* functions */
PyObject* functionName(PyObject* self, PyObject* args) {
	return PyUnicode_FromString("This is return value.");
}


/* method definitions */
static PyMethodDef mymoduleMethods[] = {	/* name of your method def */
	{
		"functionName", 			// name of function (for call from .py file)
		functionName, 				// name of function in cpp file
		METH_VARARGS, 				// type of arguments (METH_VARARGS is fine most of the time)
		"A functions description."	// description of the function
	},	
	// more functions
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