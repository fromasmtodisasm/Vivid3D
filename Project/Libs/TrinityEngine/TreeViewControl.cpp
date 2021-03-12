#include "pch.h"
#include "TreeViewControl.h"
#include "UI.h"
#include "Application.h"

TreeViewControl::TreeViewControl()
{

	Bg = new Texture2D("edit/white1.png", false);
	Scroller = new VerticalScrollerControl();
	AddControl(Scroller);

}

void TreeViewControl::AfterSet() {

	Scroller->Set(GetW() - 12, 0, 11, GetH());


}

void TreeViewControl::SetScroller() {

	int th = GetTreeH(Root,5);

	printf("TH:%d \n", th);
	Scroller->SetMax(th-(Application::WinH-350));
	Scroller->SetCur(0);
	OffY = 0;

	auto changed = [&] {

		float v = Scroller->GetCur();
		printf("Val:%f \n", v);
		OffY = v;


	};
	Scroller->SetChanged(changed);




}

int TreeViewControl::GetTreeH(TreeItem* it,int y) {

	if (it->Open) {

		y = y + 25;

		for (int i = 0; i < it->Sub.size(); i++) {

			auto i1 = it->Sub[i];

			y = GetTreeH(i1,y);
			
		}

		return y;

	}
	else {
		y = y + 25;
		return y;
	}

}

TreeItem* TreeViewControl::AddItem(const char* text) {

	auto r = new TreeItem;

	r->SetText(text);

	return r;

}

void TreeViewControl::SetRoot(TreeItem* node) {

	Root = node;

}

int TreeViewControl::RenderNode(TreeItem* node, int x, int y) {

	if (y > GetY()+GetH() - 20)
	{
		return y;
	}

	bool dr = false;
	if (y < GetY()) {
		dr = true;
	}

	if (Over == node) {

		if (!dr) {
			UI::DrawTexture(Bg, GetX() + 2, y - 2, GetW() - 4, 22, 0.1f, 0.1f, 0.1f, 1.0f);
		}
	}
	
	if (Active == node) {

		if (!dr) {
			UI::DrawTexture(Bg, GetX() + 2, y - 2, GetW() - 4, 22, 0.1f, 0.5f, 0.5f, 1.0f);
		}
	}
	


	if (node->Icon != NULL) {
		if (!dr) {
			UI::DrawTexture(node->Icon, x + 15 + UI::TextWidth(node->GetText()) + 5, y, 12, 12, 1, 1, 1, 1);
		}
	}
	if (!dr) {
		UI::RenderText(x + 15, y, node->GetText(), 1, 1, 1, 1);
	}

	if (!dr) {
		if (node->Sub.size() > 0) {
			UI::DrawTexture(Bg, x, y, 12, 12, 1, 1, 1, 1);
		}
	}
	if (node->Open && node->Sub.size()>0) {

		if (!dr) {
			UI::DrawTexture(Bg, x + 2, y + 2, 8, 8, 0.3f, 0.3f, 0.3f, 1.0f);
		}
		y = y + 25;

		x = x + 15;

		for (int i = 0; i < node->Sub.size(); i++) {

			auto i1 = node->Sub[i];

			y = RenderNode(i1, x, y);

			y = y + 25;

		}
		if (node->Sub.size() > 0) {
			y = y - 25;
		}

	}

	return y;

}

void TreeViewControl::Render() {
	
	UI::DrawTexture(Bg, GetX(), GetY(), GetW(), GetH(), 0.3f, 0.3f, 0.3f, 1.0f);

	RenderNode(Root,5,GetY()+5-OffY);


}


int TreeViewControl::CheckNode(TreeItem* node, int x, int y, int mx, int my) {

	if (mx > 1 && mx<GetW()-1 + UI::TextWidth(node->GetText())+25 && my>y && my < y + 25)
	{
		Over = node;
	}

	if (node->Open == false) {
		if (bd) {
			if (mx > x && mx<x + 12 && my>y && my < y + 12)
			{
				node->Open = true;
				SetScroller();
			}
		}

	}else 
	if (node->Open && node->Sub.size() > 0) {

		//UI::DrawTexture(Bg, x + 2, y + 2, 8, 8, 0.3f, 0.3f, 0.3f, 1.0f);

		if (bd) {
			if (mx > x && mx<x + 12 && my>y && my < y + 12)
			{
				node->Open = false;
				SetScroller();
			}
		}

		y = y + 25;

		x = x + 15;

		for (int i = 0; i < node->Sub.size(); i++) {

			auto i1 = node->Sub[i];

			y = CheckNode(i1, x, y,mx,my);

			y = y + 25;

		}
		if (node->Sub.size() > 0) {
			y = y - 25;
		}

	}

	return y;

}

void TreeViewControl::MouseMove(int x, int y, int dx, int dy) {

	Over = NULL;
	CheckNode(Root, 5,5-OffY,x,y);
	bd = false;

}

void TreeViewControl::MouseDown(int b) {

	if (b == 0) {

		bd = true;

		Active = Over;

		if (Active != NULL) {

			if (Active->Act != NULL) {
				Active->Act(Active);
			}

		}

	}

}