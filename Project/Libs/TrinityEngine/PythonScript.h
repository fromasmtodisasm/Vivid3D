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

#include "PythonFunc.h"


class PythonScript
{
public:

	PythonScript(const char* file);
	PythonFunc* GetFunc(const char* name);

private:

	PyObject* pName, * pModule, * pFunc, * pArgs, * pValue;

};

