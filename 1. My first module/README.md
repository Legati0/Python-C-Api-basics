# Overview

This directory shows a basic Python Extension written in C++.

You'll need at least 2 files for a working extension: `setup.py` and `<somename>.cpp`. The `<somename>.cpp` contains the sourcecode and the `setup.py` builds the Python extension from it.

To build and run this extension execute the following commands.

`$ python3 setup.py build`

`$ python3 setup.py install `

`$ python3 main.py `

`main.py` is just a file for testing that the module works.

---

# The \<somename\>.cpp file

## Includes

You have to include the `Python.h` header. It is also advised to define `PY_SSIZE_T_CLEAN` before everything else.

```
#define PY_SSIZE_T_CLEAN
#include <Python.h>
```

## Functions

Functions (almost) always have the following format:

```
PyObject* <functionname>(PyObject* self, PyObject* args) {/*...*/}
```

In `args` the function recieves the parameters. How to extract those is explained elsewhere. The function also always returns a `PyObject*`. Return values are also explained elsewhere.

## Module Method Definition

The method defintion has the following format:

```
static struct PyModuleDef <modulename>Methods[] = {
    {"<callname>", <functionname>, <type of args>, "<function description>"},
    //...
	{NULL, NULL, 0, NULL}	/* Sentinel */
};
```

The callname is how this function is called from python files. The functionname corresponds to one of the functions. Type of args are in most cases `METH_VARARGS` (other types won't be discussed here). The function description is just a short description of what the function does.

## Module Definition

The module definition has the following format:

```
static struct PyModuleDef <modulename>def = {
	PyModuleDef_HEAD_INIT,
	"<modulename>",
	"<module documentation>",
	-1,
	<modulename>Methods
};
```

## Module Initialization

The module initialization has the following format:

```
PyMODINIT_FUNC
PyInit_<modulename>(void) {
	PyObject* m = PyModule_Create(&<modulename>def);
	if (m == NULL)
		return NULL;
	return m;
}
```

---

# The setup<span></span>.py file

The `setup.py` is the file that actually builds the extension. It has the following format:

```
import os
from setuptools import setup, Extension

module = Extension('<modulename>',
					sources=['<somename>.cpp'],
					include_dirs=['.'],
					language='c++')

setup(name='<modulename>',
	ext_modules = [module])
```

The `sources` include all of your C++ source files.
