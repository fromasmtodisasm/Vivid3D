#include "pch.h"
#include "PythonMod.h"

PythonMod::PythonMod(PyObject* pmod) {

	mod = pmod;

}

PythonFunc* PythonMod::GetFunc(const char* name) {

	return new PythonFunc(PyObject_GetAttrString(mod, name));

}

PythonClass* PythonMod::GetClass(const char* name) {

	PyObject* dict = PyModule_GetDict(mod);
	PyObject* cls = PyDict_GetItemString(dict, name);
	if (cls == nullptr) {
		printf("Failed to obtain class.\n");

	}
	return new PythonClass(cls);

}