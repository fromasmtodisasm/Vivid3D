#include "pch.h"
#include "WindowControl.h"
#include "UI.h"
#include "UITheme.h"
#include "ButtonControl.h"

WindowControl::WindowControl() {

	Title = new ButtonControl();
	Resize = new ButtonControl();
	VScroller = new VerticalScrollerControl();

	auto act_drag = [&](int x,int y) {

		SetX(GetInternalX() + x);
		SetY(GetInternalY() + y);
	
//		b2->Set(b2->GetX() + 5, b2->GetY(), b2->GetW(), b2->GetH());

	};

	auto act_size = [&](int x, int y) {

		int w = GetW(), h = GetH();
		SetSize(GetW() + x, GetH() + y);
		if (GetW() < 10 || GetH()<25)
		{
			SetSize(w, h);
		}

	};

	Title->SetDrag(act_drag);

	Resize->SetDrag(act_size);

	Body = new UIControl();

	Body->SetCull(true);

	Resize->SetText("\n");

	Title->SetText("Window\n");

	AddControl(Title);
	AddControl(Body);
	AddControl(Resize);
	AddControl(VScroller);

	Resized();

};

void WindowControl::Resized() {

	Title->Set(0, 0, GetW(), 20);
	Body->Set(0, 20, GetW(), GetH() - 20);
	Resize->Set(GetW()-12,GetH()-12, 12, 12);
	VScroller->Set(GetW() - 12, 20, 12, GetH()-32);
//	exit(0);


	int my = Body->GetContentsH();

	printf("MY:%d H:%d\n", my, GetH());

	if ((GetH()-20) < my) {

		for (int i = 0;i < Controls.size();i++) {

			if (Controls[i] == VScroller)
			{
				return;
			}

		}
		AddControl(VScroller);
		VScroller->SetCur(0);
		VScroller->SetMax(my);

		auto changed = [&] {

			printf("Cur:%d \n", VScroller->GetCur());
			int cur = VScroller->GetCur();
		
			for (int i = 0;i < Body->ControlsCount();i++) {

				auto bc = Body->GetControl(i);
				bc->SetOffset(0, -cur);

			}

		};

		VScroller->SetChanged(changed);

	}
	else {
 
		for (int i = 0;i < Controls.size();i++) {
			if (Controls[i] == VScroller) {
				Controls.erase(Controls.begin() + i);
			}
		}

		for (int i = 0;i < Body->ControlsCount();i++) {
			auto bc = Body->GetControl(i);
			bc->SetOffset(0, 0);
		}
//		Controls.

	}

};

void WindowControl::Render() {

	Title->SetText(GetText());
	UI::Theme->DrawFrame(GetX(), GetY(), GetW(), GetH(), 1,1,1,1);

}
