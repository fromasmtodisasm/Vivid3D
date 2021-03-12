#pragma once
#include "UI.h"
#include "UIControl.h"
#include "Texture2D.h"

class ContentBrowserControl;

class ContentItem : public UIControl
{
public:
	ContentItem(const char* path,const char* name,const char * ext,bool folder,Texture2D* img);
	bool IsFold() {
		return IsFolder;
	}
	void Render();
	void DoubleClick(int b);
	void MouseEnter();
	void MouseLeave();
	void MouseDown(int b);
	void MouseUp(int b);
	void SetDC(std::function<void()> a)
	{
		act = a;
	}
	const char* GetPath()
	{
		return FullPath;
	}
	void SetBrowser(ContentBrowserControl* browser) {
		Browser = browser;
	}
private:
	bool highlight = false;
	bool IsFolder = false;
	const char* FullPath;
	const char* Name;
	const char* Ext;
	Texture2D* Img;
	std::function<void()> act = NULL;
	ContentBrowserControl* Browser;
};

