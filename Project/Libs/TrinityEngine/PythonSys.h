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

#include "PythonMod.h"


class PythonSys
{
public:
	PythonSys();
	void Free();
	void RunString(const char* code);
	void RunFile(const char* file);
	//void ImportFile(const char* file);

	PythonMod* ImportFile(const char* file);

	static PythonSys* Main;

private:
	wchar_t* program;
	std::vector<PyObject*> mods;

};


