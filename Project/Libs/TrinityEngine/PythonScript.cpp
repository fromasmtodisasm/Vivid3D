#include "pch.h"
#include "PythonScript.h"

PythonScript::PythonScript(const char* path) {

	printf("Calling\n");
	pName = PyUnicode_FromString(path);
	printf("called\n");

	pModule = PyImport_Import(pName);
	

}

PythonFunc* PythonScript::GetFunc(const char* name) {

	PyObject* f = PyObject_GetAttrString(pModule, (char*)name);

	return new PythonFunc(f);

}