#pragma once
#include "UIControl.h"
#include<vector>
#include "Texture2D.h"

struct ListItem {

	const char* Text;
	Texture2D* Icon;
	std::function<void(ListItem* item)> Act = NULL;
	void* Data = NULL;


};

class ListControl :
	public UIControl
{
public:
	
	ListControl();

	ListItem * AddItem(const char* text);
	void ClearItems() {
		Items.resize(0);
	}
	void MouseEnter();
	void MouseLeave();
	void MouseDown(int b);
	void MouseMove(int x, int y, int dx, int dy);

	void Render();


private:
	std::vector<ListItem*> Items;
	ListItem* Over;
	ListItem* Active;
	Texture2D* White;
};

