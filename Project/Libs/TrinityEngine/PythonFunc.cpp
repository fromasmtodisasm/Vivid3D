#include "pch.h"
#include "PythonFunc.h"

PythonFunc::PythonFunc(PyObject* f) {

	func = f;

}

PythonReturn* PythonFunc::Call() {

	return new PythonReturn(PyObject_CallObject(func, NULL));


}

void PythonFunc::BeginPars(int num) {

	args = PyTuple_New((Py_ssize_t)num);
	ic = 0;

}

void PythonFunc::AddInt(int v) {

    PyObject *nv = PyLong_FromLong((long)v);
	PyTuple_SetItem(args, ic, nv);
	ic++;
}

void PythonFunc::AddPtr(void* ptr) {

	PyObject* nv = PyLong_FromVoidPtr(ptr);

	PyTuple_SetItem(args, ic, nv);
	ic++;

}

void PythonFunc::AddString(const char* str) {

	PyObject* nv = PyUnicode_FromString(str);
	PyTuple_SetItem(args, ic, nv);
	ic++;

}

void PythonFunc::AddObj(PythonObj* o) {

	PyTuple_SetItem(args, ic, o->GetObj());
	ic++;

}

PythonReturn* PythonFunc::CallPars() {

	ret = PyObject_CallObject(func, args);
	return new PythonReturn(ret);

}
