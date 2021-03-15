#pragma once
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
class PythonObj
{
public:
	PythonObj(PyObject* o)
	{
		obj = o;
	}
	PyObject* GetObj() {
		return obj;
	}
private:
	PyObject* obj;
};

