#include "pch.h"
#include "MonoRT.h"


MonoRT::MonoRT() {

	domain = mono_jit_init("test");

}