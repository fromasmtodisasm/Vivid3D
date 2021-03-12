#include "ContentItem.h"
#include <stdio.h>
#include "MapTile.h"
#include "ContentBrowserControl.h"
#include "strings.h"
#include "TileEditorControl.h"
#include "MapEditControl.h"

ContentItem::ContentItem(const char* path,const char* name,const char * ext, bool folder,Texture2D* img) {

	IsFolder = folder;
	FullPath = path;
	printf("File:");
	printf(path);
	printf("\n");
	printf("Ext:");
	printf(ext);
	printf("\n");
	Img = img;
	Ext = ext;
	Name = name;
	if (strSame(Ext, ".jpg") || strSame(Ext,".png")) {

		Img = new Texture2D(FullPath, false, true);

	}
	canDrag = true;
	SetData((void*)Img);
	return;
	int sl = strlen(FullPath);
	int sp = -1;
	for (int i = 0;i < sl;i++) {
		if (FullPath[i] == "\\"[0] || FullPath[i] == "/"[0])
		{
			sp = i;
		}
	}


	if (sp > -1) {
		int nl = sl - sp;
		//Name = (const char*)malloc(nl+1);


		char* nn = (char*)malloc(nl + 1);

		int nc = 0;
		for (int i = sp+1;i < sl ;i++) {
			nn[nc] = FullPath[i];
			nc++;
		}
		nn[sl] = "\n"[0];
		Name = nn;
	}
	else {
		Name = FullPath;
	}

	

}

void ContentItem::DoubleClick(int b) {

	Browser->ScanDir(FullPath);

}

int cd = 0;

void ContentItem::MouseDown(int b) {

	if (b == 0)
	{

		cd = (int)clock();

	}

}
void ContentItem::MouseUp(int b) {
	if (b == 0) {

		int nt = (int)clock();
		if ((nt - cd) < 250)
		{

			if (strSame(Ext, ".jpg") || strSame(Ext,".png"))
			{

				MapTile* tile = new MapTile(FullPath);
				TileEditorControl::SetTile(tile);
				MapEditControl::CurTile = tile;

			}
		}

	}
}

void ContentItem::Render() {

	if (highlight) {

		UI::DrawTexture(Img, GetX() - 2, GetY() - 2, GetW() + 4, GetH() + 4, 0.1f, 0.1f, 1, 1);

	}
	UI::DrawTexture(Img, GetX(), GetY(), GetW(), GetH(), 1, 1, 1, 1);

	UI::RenderText(GetX() + 2, GetY() + 70, Name, 1, 1, 1, 1);

}

void ContentItem::MouseEnter() {

	highlight = true;
}

void ContentItem::MouseLeave() {

	highlight = false;

}