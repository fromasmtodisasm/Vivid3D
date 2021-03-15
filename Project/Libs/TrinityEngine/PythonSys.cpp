#include "pch.h"
#include "PythonSys.h"


PythonSys::PythonSys() {

	//Py_SetProgramName("VividScript");
	Py_Initialize();
	mods.resize(0);
	Main = this;
}

PythonSys* PythonSys::Main = NULL;

void PythonSys::RunString(const char* str) {

	PyRun_SimpleString(str);

}

void PythonSys::RunFile(const char* path) {

	//PyRun_SimpleFile(path);
//	PyRun_SimpleFile()


}

PythonMod* PythonSys::ImportFile(const char* path) {

	PyObject* name = PyUnicode_FromString((char*)path);
	PyObject* mod = PyImport_Import(name);
	return new PythonMod(mod);


	mods.push_back(mod);
}


void PythonSys::Free() {

	Py_Finalize();

}