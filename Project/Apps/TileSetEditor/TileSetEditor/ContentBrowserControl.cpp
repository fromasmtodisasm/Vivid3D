#include "ContentBrowserControl.h"
#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;
#include "UI.h"
#include "UITheme.h"

void ContentBrowserControl::ScanDir(const char* path) {

	printf("Scanning:");
	printf(path);
	printf("\n");

	paths.push(path);

	Items.resize(0);
	std::string p = std::string(path);

	Texture2D* fileImg = new Texture2D("Edit/fileicon.png",true);
	Texture2D* folderImg = new Texture2D("Edit/foldericon.png",true);

	for (const auto& entry : fs::directory_iterator(p))
	{
		ContentItem* item;
		if (entry.is_directory())
		{
			std::cout << "Folder:" << entry.path() << std::endl;
			
			std::string fpath = entry.path().string();

			std::string name = entry.path().filename().string();

			char* nn = (char*)malloc(name.length()+1);

			for (int cn = 0;cn < name.length();cn++) {
				nn[cn] = name.c_str()[cn];
			}

			nn[name.length()] = "\0"[0];

			std::cout << "FILE:" << name << std::endl;

			 char* npath = (char *)malloc(fpath.length() + 1);

			const char* pp = fpath.c_str();

			for (int i = 0;i < fpath.length();i++) {

				npath[i] = pp[i];

			}

			npath[fpath.length()] = "\0"[0];
			//npath[fpath.length() + 1] = "\0"[0];


			
			item = new ContentItem(npath,nn,"", true,folderImg);

			

		}
		else {
			std::cout << "File:" << entry.path() << std::endl;

			std::string fpath = entry.path().string();
			std::string name = entry.path().filename().string();
			char* npath = (char*)malloc(fpath.length() + 1);

			std::string ext = entry.path().extension().string();

			char* next = (char*)malloc(ext.length() + 1);

			for (int i = 0;i < ext.length();i++) {
				next[i] = ext[i];
			}
			next[ext.length()] = "\0"[0];

			const char* pp = fpath.c_str();

			for (int i = 0;i < fpath.length();i++) {

				npath[i] = pp[i];

			}
			char* nn = (char*)malloc(name.length() + 1);

			for (int cn = 0;cn < name.length();cn++) {
				nn[cn] = name.c_str()[cn];
			}

			nn[name.length()] = "\0"[0];

			npath[fpath.length()] = "\0"[0];

			item = new ContentItem(npath,nn,next, false,fileImg);
		}
		Items.push_back(item);
		//while (true) {}

	}

	//Body->ClearChild();

	ClearChild();
	int ix, iy;

	ix = 8;
	iy = 8;

	for (int i = 0;i < Items.size();i++) {

		auto item = Items[i];

		if (item->IsFold()) {

			item->Set(ix, iy, 64, 64);
			ix += 128;
			if (ix > GetW() - 128)
			{
				ix = 5;
				iy = iy + 128;
			}
			AddControl(item);
			item->SetBrowser(this);
		}

		

	}

	for (int i = 0;i < Items.size();i++) {

		auto item = Items[i];

		if (!item->IsFold()) {

			item->Set(ix, iy, 64, 64);
			ix += 128;
			if (ix > GetW() - 128)
			{
				ix = 5;
				iy = iy + 128;
			}
			AddControl(item);

		}


	}

}

void ContentBrowserControl::MouseDown(int b) {
	//exit(0);
	
	

	if (b == 1) {

		if (paths.size() > 1) {
			paths.pop();
			ScanDir(paths.top());
			paths.pop();
		}

	}

	

}

void ContentBrowserControl::Render() {


	UI::Theme->DrawFrame(GetX(), GetY(), GetW(), GetH(), 1, 1, 1, 1);

}