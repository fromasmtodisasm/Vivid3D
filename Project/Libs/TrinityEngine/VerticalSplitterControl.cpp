#include "pch.h"
#include "VerticalSplitterControl.h"
#include "UI.h"
#include "UITheme.h"

void VerticalSplitterControl::Resized() {


	if (Top != NULL) {
		Top->Set(0, 0,GetW(),SplitPos-4);
	}
	if (Bottom != NULL) {
		Bottom->Set(0,SplitPos+4, GetW(),GetH() - (SplitPos + 4));
	}
	if (SplitPos < 0) {
		SplitPos = GetH() / 2;
	}

};

void VerticalSplitterControl::Render() {


	//UI::Theme->DrawFrame(GetX(), GetY(), GetW(), SplitPos - 4,0.6f,0.8f,0.8f,1.0f);
	UI::Theme->DrawFrame(GetX(), GetY() + SplitPos - 2, GetW(), 5, 0.5f,0.5f,0.5f, 1);
	UI::Theme->DrawFrame(GetX(), GetY() + SplitPos - 1, GetW(), 2,1,1,1, 1.0f);
//	UI::Theme->DrawFrame(GetY(), GetY() + SplitPos + 4, GetW(), GetH() - (SplitPos + 4),0.6f,0.8f,0.8f,1);

	//UI::Theme->DrawFrame(GetX(), GetY()+SplitPos-4, GetW(), GetY()+SplitPos+4, 0.8f, 0.8f, 0.8f, 1);
	//UI::Theme->DrawFrame(SplitPos + 4, GetY(), GetW() - (SplitPos + 4), GetH(), 0.8f, 0.8f, 0.8f, 1);


};

void VerticalSplitterControl::MouseDown(int b) {

	if (OverDrag) {

		Dragging = true;

	}

}

void VerticalSplitterControl::MouseUp(int b) {

	Dragging = false;


};

void VerticalSplitterControl::MouseMove(int x, int y, int mx, int my) {

	//printf("XM:%d YM:%d\n", mx, my);

	if (!Dragging) {

		if (x>=GetX() && x<=GetX()+GetW()) {
			if (y >= (SplitPos-4) && y<= (SplitPos+4))
			{
				OverDrag = true;

			}
			else {
				OverDrag = false;
			}

		}
		else {
			OverDrag = false;
		}

	}
	else {

		SplitPos += my;
		if (SplitPos < 10) {
			SplitPos = 10;
		}
		if (SplitPos > (GetH() - 5))
		{
			SplitPos = GetH() - 10;
		}
		Resized();

	}

	//SplitPos += mx;

}

