#pragma once
#include "UIControl.h"
#include "WindowControl.h"
#include "ButtonControl.h"
#include "ListControl.h"
//#include <filesystem>
//#include <filesystem>
#include <string>
#include <iostream>
#include <string>
#include <iostream>
#include <filesystem>
#include "TextBoxControl.h"
namespace fs = std::filesystem;

class FileRequestorControl : public WindowControl
{
public:

	FileRequestorControl() {
	
		FolderIcon = new Texture2D("edit/foldericon.png",true);
		Cur = this;
	}

	static FileRequestorControl* Cur;

	const char* DirPath = "";

	void SetSelected(std::function<void(const char* path)> sel) {
		Selected = sel;
	}

	void SetDir(const char* ipath) {

		DirPath = ipath;
		View->ClearItems();
		for (const auto& entry : fs::directory_iterator(ipath))
		{
		//	ContentItem* item;

			printf("File:");
			printf((const char*)entry.path().filename().c_str());
			printf("\n");
			if (entry.is_directory())
			{
				std::string fpath = entry.path().string();

				std::string name = entry.path().filename().string();

				char* nn = (char*)malloc(name.length() + 1);

				for (int cn = 0; cn < name.length(); cn++) {
					nn[cn] = name.c_str()[cn];
				}

				nn[name.length()] = "\0"[0];

				std::cout << "FILE:" << name << std::endl;

				char* npath = (char*)malloc(fpath.length() + 1);

				const char* pp = fpath.c_str();

				for (int i = 0; i < fpath.length(); i++) {

					npath[i] = pp[i];

				}

				npath[fpath.length()] = "\0"[0];
				//npath[fpath.length() + 1] = "\0"[0];


				auto item = View->AddItem((const char*)nn);
				item->Icon = FolderIcon;
				item->Data = (void*)VString(fpath.c_str()).GetConst();

				auto fAct = [&](ListItem* i)
				{
					FileRequestorControl::Cur->SetDir((const char*)i->Data);
				};

				item->Act = fAct;

			}
			else {

				std::string fpath = entry.path().string();

				std::string name = entry.path().filename().string();

				char* nn = (char*)malloc(name.length() + 1);

				for (int cn = 0; cn < name.length(); cn++) {
					nn[cn] = name.c_str()[cn];
				}

				nn[name.length()] = "\0"[0];

				std::cout << "FILE:" << name << std::endl;

				char* npath = (char*)malloc(fpath.length() + 1);

				const char* pp = fpath.c_str();

				for (int i = 0; i < fpath.length(); i++) {

					npath[i] = pp[i];

				}

				npath[fpath.length()] = "\0"[0];

				auto i = View->AddItem((const char*)nn);

				auto fAct = [&](ListItem* i) {

					File->SetText(i->Text);
					//File->SetData((void*)VString(fpath.c_str()).GetConst());



				};

				i->Act = fAct;

			}
		}

	};

	void Resized() {

		WindowControl::Resized();

		if (OK == NULL) {
			OK = new ButtonControl();
			Cancel = new ButtonControl();
			View = new ListControl();
			File = new TextBoxControl();

			auto aOK = [&]() {
				
				auto fpath = (char*)File->GetText();
				VString path(DirPath);
				if (path.GetChar(path.Len() - 1) != "\\"[0])
				{
					path.Add("\\");
				}

				
				path.Add(VString(File->GetText()));

				if (Selected != NULL) {
					Selected(path.GetConst());
				}

			};

			OK->SetAction(aOK);

			File->Set(5, 30 + GetH() - 90, GetW() - 30, 25);
			View->Set(5, 35, GetW() - 30, GetH() - 100);


			OK->Set(5, GetH() - 30, 120, 25);
			Cancel->Set(130, GetH() - 30, 120, 25);

			//View->AddItem("File1/n");
//			View->AddItem("File2/n");

			OK->SetText("OK!\n");
			Cancel->SetText("Cancel\n");

			AddControl(View);
			AddControl(OK);
			AddControl(File);
			AddControl(Cancel);
		}

	};
	

private:

	ButtonControl* OK = NULL;
	ButtonControl* Cancel = NULL;
	TextBoxControl* File;
	ListControl* View;
	const char* Path = "";
	Texture2D* FolderIcon;
	Texture2D* FileIcon;
	std::function<void(const char* path)> Selected = NULL;

};

