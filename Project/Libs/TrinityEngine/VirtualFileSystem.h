#pragma once
#include "VirtualFile.h"
#include <vector>
class VirtualFileSystem
{
public:
	VirtualFileSystem(const char* base);
	void ScanBase();
	void ScanDir(const char* path);
	void SaveFS(const char* name);
	void LoadAndCompress();

private:
	const char* BasePath = "";
	std::vector<VirtualFile*> Files;
	
};

