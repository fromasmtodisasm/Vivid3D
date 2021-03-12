#include "pch.h"
#include "ToolsControl.h"
#include "UI.h"
#include "ImageControl.h"
ToolsControl::ToolsControl() {

	White = new Texture2D("Edit/White1.png", false);
	IX = 5;
}

void ToolsControl::Render() {

	UI::DrawTexture(White, GetX(), GetY(), GetW(), GetH(), 0.25f, 0.25f, 0.25f, 1.0f);

}

void ToolsControl::AddSeperator() {

	ImageControl* c = new ImageControl(White);

	//c->SetT


	c->SetX(IX+12);
	c->SetY(3);



	int w = 1;
	int h = 33;

	c->SetSize(w, h);
	AddControl(c);
	IX = IX + 30;

}

void ToolsControl::AddItem(UIControl* c) {

	
	c->SetX(IX);
	c->SetY(3);

	int w = UI::TextWidth(c->GetText()) + 15;
	int h = 30;

	c->SetSize(w, h);
	AddControl(c);
	IX = IX + c->GetW() + 3;
}

ButtonControl* ToolsControl::AddItem(const char* name) {

	int iw = UI::TextWidth(name);

	auto b = new ButtonControl();
	b->Set(IX, 4, iw + 10, 18);
	b->SetText(name);
	IX = IX + iw + 15;
	AddControl(b);

	return b;

}