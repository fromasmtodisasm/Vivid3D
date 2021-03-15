#include "pch.h"
#include "PythonReturn.h"

int PythonReturn::ReturnInt() {

	return (int)PyLong_AsLong(rv);

}

PythonObj* PythonReturn::ReturnObj() {

	return new PythonObj(rv);

}