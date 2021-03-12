#pragma once
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class LScript
{
public:

		LScript();
		void RunFile(const char* path);
		void PushCall(const char* name);
		void PushNum(float num);
		void PushString(const char* str);
		void PushBool(bool b);
		void PushNil();
		void Call(int cnum, int rnum);
		int GetInt(int index);
		float GetFloat(int index);
		const char* GetString(int index);
		bool GetBool(int index);
		void Pop(int num);
		const char* GetPath();

private:

	lua_State* state;
	const char* spath;

};


