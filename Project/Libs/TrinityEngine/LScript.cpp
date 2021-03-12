#include "pch.h"
#include "LScript.h"
#include "VString.h"
LScript::LScript() {

	state = luaL_newstate();
	luaL_openlibs(state);

}

void LScript::RunFile(const char* path) {

	luaL_dofile(state, path);
	spath = VString(path).GetConst();

}

const char* LScript::GetPath() {

	return spath;

}

void LScript::PushCall(const char* name) {

	lua_getglobal(state, name);

}

void LScript::PushNum(float v) {

	lua_pushnumber(state,(lua_Number) v);

}

void LScript::PushString(const char* str) {

	lua_pushstring(state, str);

}

void LScript::PushBool(bool s) {

	lua_pushboolean(state, s);

}

void LScript::Call(int cnum, int rnum) {

	lua_call(state, cnum, rnum);

}

float LScript::GetFloat(int index) {

	return (float)lua_tonumber(state, index);

}

int LScript::GetInt(int index) {

	return (int)lua_tointeger(state, index);

}

const char* LScript::GetString(int index) {

	return (const char*)lua_tostring(state, index);

}

bool LScript::GetBool(int index) {

	return (bool)lua_toboolean(state, index);

}

void LScript::Pop(int num) {

	lua_pop(state, num);

}
