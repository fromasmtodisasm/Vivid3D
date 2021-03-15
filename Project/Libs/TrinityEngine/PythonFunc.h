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
#include "PythonReturn.h"
class PythonFunc
{
public:

	PythonFunc(PyObject* f);
	PythonReturn* Call();
	void BeginPars(int num);
	void AddInt(int v);
	void AddString(const char* str);
	void AddPtr(void* ptr);
	void AddObj(PythonObj* o);
	PythonReturn* CallPars();
	


private:
	PyObject* func;
	PyObject* args;
	int ic = 0;
	PyObject* ret;
};

