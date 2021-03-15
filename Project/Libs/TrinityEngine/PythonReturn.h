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
#include "PythonObj.h"
class PythonReturn
{
public:
	PythonReturn(PyObject* v) {
		rv = v;
	}
	int ReturnInt();
	PythonObj* ReturnObj();
private:
	PyObject* rv;
};

