#pragma once
#define PY_SSIZE_T_CLEAN
#ifdef _DEBUG
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#endif

#include "Python.h"

#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif
#include "PythonReturn.h"
class PythonClass
{
public:
	PythonClass(PyObject* obj)
	{
		cls = obj;
	}

	PythonClass* CreateInstance() {

		return new PythonClass(PyObject_CallObject(cls, NULL));

	}

	PythonReturn* CallMethod(const char* str) {

		return new PythonReturn(PyObject_CallMethod(cls, str,"(i)", 25));

	}

private:
	PyObject* cls;

};


