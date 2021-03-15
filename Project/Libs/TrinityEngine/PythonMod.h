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
#include "PythonClass.h"
class PythonMod
{
public:
	PythonMod(PyObject* mod);
	PythonFunc* GetFunc(const char* name);
	PythonClass* GetClass(const char* name);
private:
	PyObject* mod;
};

