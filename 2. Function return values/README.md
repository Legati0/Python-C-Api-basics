# Overview

In this directory you well learn how to return values from your module functions. See `mymodule.cpp` for code examples.

---

# Return Values of functions

As the function declaration tells you, each function returns a PyObject (pointer). This is the same as in python. There are no void functions, as every function has to return at least `None`.
This means you just have to convert your `c++` datatypes to a python datatype. This can be done by using conversion functions like for example `PyObject* PyLong_FromLong(long v)` or by using the `PyObject* Py_BuildValue(char *format, ...)` function (recommended).
For the format of `Py_BuildValue` see [here](http://decstation.unix-ag.org/docs/python/ext/node11.html) and [doc here](https://docs.python.org/3/c-api/arg.html) for other conversion functions see [doc](https://docs.python.org/3/c-api/concrete.html).

For errors return `NULL`.

---

# Examples

## Possible ways to return `None`:

```
return Py_BuildValue(""); // recommended

return Py_None;

Py_RETURN_NONE;
```

## Possible ways to return a `bool` value:

```
return Py_True;

Py_RETURN_TRUE;

return Py_False;

Py_RETURN_FALSE;
```

## Possible ways to return a `int` value:

```
return Py_BuildValue("i", 123);

return PyLong_FromLong(123);
```

## Possible ways to return a `float` value:

```
return Py_BuildValue("d", 123.456);

return PyFloat_FromDouble(123.456);
```

## Possible ways to return a `string` value:

```
return Py_BuildValue("s", "hello");

return PyUnicode_FromString("hello");
```

## Possible ways to return a `tuple` of fixed size:

```
return Py_BuildValue("(ii)", 123, 456);

return Py_BuildValue("ii", 123, 456);	// implicit parentheses

return Py_BuildValue("is", 123, "hello");	// mixed types
```

## Possible ways to return a 2d `tuple` of fixed size:

```
return Py_BuildValue("((ii)(ii))", 123, 456, 123, 456);

return Py_BuildValue("(ii)(ii)", 123, 456, 123, 456);	// implicit parentheses
```

## Possible way to return a `tuple` of varying size:

```
std::vector<long> v {1, 2, 3, 4, 5, 6};
PyObject* tuple = PyTuple_New(v.size());	// create a new tuple, size is important
unsigned int index = 0;
for (auto& elem : v) {
	PyObject* obj = PyLong_FromLong(elem);	// can be inlined
	if (PyTuple_SetItem(tuple, index++, obj) == -1)	// set item at each index
		return NULL;	// indexerror
}
return tuple;
```

## Possible way to return a 2d `tuple` of varying size:

```
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
```

## Possible ways to return a `list` of fixed size:

```
return Py_BuildValue("[ii]", 123, 456);

return Py_BuildValue("[is]", 123, "hello");	// mixed types
```

## Possible way to return a 2d `list` of fixed size:

```
return Py_BuildValue("[[ii][ii]]", 123, 456, 123, 456);
```

## Possible way to return a `list` of varying size:

```
std::vector<long> v {1, 2, 3, 4, 5, 6};
PyObject* list = PyList_New(0);		// create new list, size is not important, just use 0
for (auto& elem : v) {
	PyObject* obj = PyLong_FromLong(elem);	// can be inlined
	if (PyList_Append(list, obj) == -1)	// append item to list
		return NULL;	// some error
}
return list;
```

## Possible way to return a 2d `list` of varying size:

```
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
```
