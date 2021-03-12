#include "pch.h"
#include "ListControl.h"
#include "UI.h"
#include "UITheme.h"
#include "UITheme_Neon.h"

ListControl::ListControl() {

	Items.resize(0);
	Over = NULL;
	Active = NULL;
	White = new Texture2D("edit/white1.png", false);

}

ListItem* ListControl::AddItem(const char* text) {


	ListItem* item = new ListItem;
	item->Text = text;
	item->Icon = NULL;
	Items.push_back(item);
	return item;

};

void ListControl::MouseMove(int x, int y, int xd, int yd) {

	int dy = 5;
	for (int i = 0; i < Items.size(); i++) {

		auto item = Items[i];

		if (x > 0 && x<GetW() && y>dy && y < dy + UI::TextHeight(item->Text) + 4) {

			Over = item;

		}


		dy = dy + UI::TextHeight(item->Text) + 4;
	}


}

void ListControl::MouseEnter() {

}

void ListControl::MouseLeave() {

}

void ListControl::MouseDown(int b) {
	if (Over != NULL) {

		if (Over->Act != NULL) {

			Over->Act(Over);

		}

	}
}

void ListControl::Render() {

	UI::Theme->DrawFrame(GetX(), GetY(), GetW(), GetH(), 3, 3, 3, 1);

	int dy = 5;

	for (int i = 0; i < Items.size(); i++) {

		auto it = Items[i];

		if (it == Over) {

			UI::DrawTexture(White, GetX() + 2, GetY() + dy, GetW() - 4, 15, 0.3f, 0.3f, 0.3f, 0.7f);

		}

		if (it->Icon != NULL) {

			UI::DrawTexture(it->Icon, GetX() + 6, GetY() + dy, 16, 16, 1, 1, 1, 1);
			UI::RenderText(GetX() + 24, GetY() + dy, it->Text, 0.3f, 0.3f, 0.3f, 1.0f);
		}
		else {
			UI::RenderText(GetX() + 6, GetY() + dy, it->Text, 0.3f, 0.3f, 0.3f, 1.0f);
			//exit(1);
		}
		dy = dy + UI::TextHeight(it->Text) + 4;
	}

}