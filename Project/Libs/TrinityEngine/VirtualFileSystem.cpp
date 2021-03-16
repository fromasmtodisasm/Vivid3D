#include "pch.h"
#include "VirtualFileSystem.h"
#include <string>
#include <iostream>
#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
#include "VString.h"
#include "VFile.h"
#include <zlib.h>

VirtualFileSystem::VirtualFileSystem(const char* base) {

	BasePath = base;
	Files.resize(0);
	ScanBase();

}

void VirtualFileSystem::ScanBase() {

	ScanDir(BasePath);

	printf("File system scanned. Total Files:%d",Files.size());
	printf("\n");

}

void VirtualFileSystem::ScanDir(const char* path) {

	printf("Scanning Dir:");
	printf(path);
	printf(":\n");

	for (const auto& entry : fs::directory_iterator(path))
	{

		if (entry.is_directory())
		{
			std::string fpath = entry.path().string();
			ScanDir(fpath.c_str());

		}
		else {
			
			std::string fpath = entry.path().string();
			std::string name = entry.path().filename().string();
			
			VirtualFile* newFile = new VirtualFile();
			newFile->RealPath = VString(path).GetConst();
			newFile->ActualName = VString(name.c_str()).GetConst();
			
			VString vp(path);
			VString fil(name.c_str());

			vp.Add(VString("\\"));
			vp.Add(name.c_str());
			
			newFile->VirtualPath = vp.GetConst();
			
			Files.push_back(newFile);

			printf("VirtualPath:");
			printf(vp.GetConst());
			printf(":\n");



		}

	}

}

void VirtualFileSystem::LoadAndCompress() {

	for (int i = 0; i < Files.size(); i++) {

		auto fi = Files[i];

		long size = VFile::Length(fi->VirtualPath);

		printf("Name:");
		printf(fi->ActualName);
		printf(" Size:%d \n", (int)size);

		VFile* fil = new VFile(fi->VirtualPath, FileMode::Read);

		unsigned char * buf = (unsigned char *)fil->ReadBytes(size);
		
		long destLen = size * 3;

		unsigned char* dest = (unsigned char *)malloc(destLen);

		//compress(dest,(uLongf*) &destLen,(const Bytef*) buf,(uLong)size);

		printf("Original Size:%d Compressed Size:%d\n", (int)size, (int)destLen);


		fi->Compressed = true;
		fi->Loaded = true;
		fi->Data = dest;
		fi->DataSize = destLen;
		fi->OriginalSize = size;


	}

	printf("File system loaded and compressed.\n");

}

void VirtualFileSystem::SaveFS(const char* path) {

	printf("Saving file system to:");
	printf(path);
	printf("\n");

	VFile* op = new VFile(path, FileMode::Write);

	op->WriteInt(Files.size());

	long bos = 0;
	long len = 0;

	for (int i = 0; i < Files.size(); i++) {

		auto fi = Files[i];


//		if (fi->Compressed) {



		

		op->WriteString(fi->ActualName);
		op->WriteString(fi->RealPath);
		op->WriteString(fi->VirtualPath);
		op->WriteLong(bos);
		op->WriteBool(fi->Compressed);
		if (fi->Compressed) {
			op->WriteLong(fi->DataSize);
			op->WriteLong(fi->OriginalSize);
		}
		else {
			op->WriteLong(fi->DataSize);
		}
	}

	for (int i = 0; i < Files.size(); i++) {

		auto fi = Files[i];

		if (fi->Compressed) {

			op->WriteBytes(fi->Data, fi->DataSize);

		}
		else {

			op->WriteBytes(fi->Data, fi->DataSize);

		}

	}

	op->Close();


}