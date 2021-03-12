#pragma once
#include "VString.h"
class VirtualFile
{
public:
	const char* RealPath = "";
	const char* VirtualPath= "";
	const char* ActualName = "";
	long DataSize = 0;
	unsigned char* Data;
	bool Loaded = false;
	bool Compressed = false;
	long OriginalSize = 0;
};

