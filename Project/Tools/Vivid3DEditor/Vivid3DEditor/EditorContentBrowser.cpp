#include "EditorContentBrowser.h"
#include "UI.h"
#include "UITheme.h"
#include <string>
#include <iostream>
#include <filesystem>
#include "NodeEntity.h"
#include "ModelImport.h"
#include "VString.h"
#include "EditorGlobal.h"
namespace fs = std::filesystem;

EditorContentBrowser::EditorContentBrowser() {

	iFolder = new Texture2D("edit/foldericon.png", true, false);
	iFile = new Texture2D("edit/fileicon.png", true, false);
	Scroller = new VerticalScrollerControl();
	AddControl(Scroller);

}

void EditorContentBrowser::Render() {

	UI::Theme->DrawFrame(GetX(), GetY(), GetW(), GetH(), 1, 1, 1, 1);

	int dx, dy;

	dx = 5;
	dy = 5;


	for (int i = 0; i < Items.size(); i++) {

		auto it = Items[i];

		int ry = dy - OffY;

		if (ry > 0) {
			if (it->IsFolder) {

				if (OverItem == it) {

					UI::Theme->DrawImg(GetX() + dx - 2, GetY() + dy - 2, 56, 56, iFolder, 0.1f, 0.1f, 0.1f, 1);


				}
				UI::Theme->DrawImg(GetX() + dx, GetY() + dy - OffY, 52, 52, iFolder, 1, 1, 1, 1);

			}
			else {
				if (OverItem == it) {

					UI::Theme->DrawImg(GetX() + dx - 2, GetY() + dy - 2, 56, 56, iFile, 0.1f, 0.1f, 0.1f, 1);


				}

				UI::Theme->DrawImg(GetX() + dx, GetY() + dy - OffY, 52, 52, iFile, 1, 1, 1, 1);

			}



			UI::RenderText(GetX() + dx - 2, GetY() + dy + 50 - OffY, it->Name, 1, 1, 1, 1);
		}
		dx = dx + 128;

		if (dx > GetW() - 64)
		{
			dx = 5;
			dy = dy + 84;
		//	MaxY = dy;
		}


	}
	if (MaxY == 0) {
		SetScroller();
	}

}

void EditorContentBrowser::MouseDown(int b) {

	if (b == 1) {

		if (paths.size() > 1) {
			paths.pop();
			ScanDir(paths.top());
			paths.pop();
		}

	}



}

void EditorContentBrowser::SetScroller() {

	if (GetW() == 0) return;
	int dx, dy;

	dx = 5;
	dy = 5;
	MaxY = 0;

	for (int i = 0; i < Items.size(); i++) {

	

			dx = dx + 128;
			int w = GetW();
			if (dx > GetW() - 64)
			{
				dx = 5;
				dy = dy + 84;
				MaxY = dy;
			}


		

	}


	Scroller->SetMax(MaxY);
	Scroller->SetCur(0);
	OffY = 0;

	auto changed = [&] {

		float v = Scroller->GetCur();
		printf("Val:%f \n", v);
		OffY = v;


	};
	Scroller->SetChanged(changed);
}

void EditorContentBrowser::AfterSet() {

	Scroller->Set(GetW() - 12, 0, 11, GetH());
	SetScroller();

}

void EditorContentBrowser::DoubleClick(int b)
{
	if (OverItem!=NULL) {

		if (OverItem->IsFolder) {

			ScanDir(OverItem->FullPath);

		}
		else {

			VString str(OverItem->FullPath);
			VString ext(OverItem->Ext);

			if (ext.IsSame(".blend") || ext.IsSame(".b3d") || ext.IsSame(".gltf"))
			{
				ModelImport* importer = new ModelImport;

				NodeEntity* ent = importer->ImportAI(str.GetConst());
				
				EditorGlobal::EditorGraph->AddEntity(ent);

				EditorGlobal::SceneTree->Rebuild();


			}

		}

	}
}


void EditorContentBrowser::MouseMove(int x, int y, int mx, int my) {

	int dx, dy;

	dx = 5;
	dy = 5;
	OverItem = NULL;
	for (int i = 0; i < Items.size(); i++) {

		auto it = Items[i];

		if (it->IsFolder) {

			//UI::Theme->DrawImg(GetX() + dx, GetY() + dy, 52, 52, iFolder, 1, 1, 1, 1);

		}
		else {

			//UI::Theme->DrawImg(GetX() + dx, GetY() + dy, 52, 52, iFile, 1, 1, 1, 1);

		}

		if (x > dx && x<dx + 52 && y>dy && y < dy + 52)
		{
			OverItem = it;
		}

		//UI::RenderText(GetX() + dx - 2, GetY() + dy + 50, it->Name, 1, 1, 1, 1);

		dx = dx + 128;

		if (dx > GetW() - 64)
		{
			dx = 5;
			dy = dy + 84;
		}

	}


}

void EditorContentBrowser::ScanDir(const char* path) {

	Items.resize(0);
	paths.push(path);

	for (const auto& entry : fs::directory_iterator(path))
	{
		ContentItem* item;
		item = new ContentItem;
		if (entry.is_directory())
		{
			std::cout << "Folder:" << entry.path() << std::endl;

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
			item->FullPath = npath;
			item->Name = nn;
			item->IsFolder = true;




			Items.push_back(item);
		}
	}
	for (const auto& entry : fs::directory_iterator(path))
	{
		ContentItem* item;
		item = new ContentItem;

		if (!entry.is_directory()) {
			//printf("File:");
			std::cout << "File:" << entry.path() << std::endl;

			std::string fpath = entry.path().string();
			std::string name = entry.path().filename().string();
			char* npath = (char*)malloc(fpath.length() + 1);

			std::string ext = entry.path().extension().string();

			char* next = (char*)malloc(ext.length() + 1);

			for (int i = 0; i < ext.length(); i++) {
				next[i] = ext[i];
			}
			next[ext.length()] = "\0"[0];

			const char* pp = fpath.c_str();

			for (int i = 0; i < fpath.length(); i++) {

				npath[i] = pp[i];

			}
			char* nn = (char*)malloc(name.length() + 1);

			for (int cn = 0; cn < name.length(); cn++) {
				nn[cn] = name.c_str()[cn];
			}

			nn[name.length()] = "\0"[0];

			npath[fpath.length()] = "\0"[0];
			item->FullPath = npath;
			item->Name = nn;
			item->Ext = next;
			Items.push_back(item);
		}

	}


	printf("\n\n\n\n\n");

	for (int i = 0; i < Items.size(); i++) {

		auto it = Items[i];

		if (it->IsFolder) {
			printf("Folder:");
			printf(it->FullPath);
			printf("\n");
		}
		else {
			printf("File:");
			printf(it->FullPath);
			printf(" Ext:");
			printf(it->Ext);
			printf("\n");
		}

	}
	SetScroller();
}