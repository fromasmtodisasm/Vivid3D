#include "pch.h"
#include "HorizontalSplitterControl.h"
#include "UI.h"
#include "UITheme.h"
void HorizontalSplitterControl::Resized() {


	if (Left != NULL) {
		Left->Set(0, 0, SplitPos - 4, GetH());
	}
	if (Right != NULL) {
		Right->Set(SplitPos + 4, 0, GetW() - (SplitPos + 4), GetH());
	}
	if (SplitPos < 0) {
		SplitPos = GetW() / 2;
	}

};

void HorizontalSplitterControl::Render() {

	//UI::Theme->DrawFrame(GetX(), GetY(), SplitPos - 4, GetH(),0.8f,0.8f,0.8f,1);
	UI::Theme->DrawFrame(GetX() + SplitPos - 2, GetY(), 5, GetH(),0.3f,0.3f,0.3f,1);
	UI::Theme->DrawFrame(GetX() + SplitPos, GetY(), 2, GetH(), 1, 1, 1, 1);
//	printf("HSX:%d HSY:%d \n", SplitPos, 0);
// 
//	printf("GX:%d GY:%d H:%d\n", GetX(), GetY(), GetH());
	//UI::Theme->DrawFrame(SplitPos + 4, GetY(), GetW() - (SplitPos + 4), GetH(),0.8f,0.8f,0.8f,1);


};

void HorizontalSplitterControl::MouseDown(int b) {

	if (OverDrag) {

		Dragging = true;

	}

}

void HorizontalSplitterControl::MouseUp(int b) {

	Dragging = false;


};

void HorizontalSplitterControl::MouseMove(int x, int y, int mx, int my) {




	if (!Dragging) {

		if (x >= (SplitPos - 2) && x <= (SplitPos +2)) {
			if (y >= 0 && y <= (GetH()))
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

		SplitPos += mx;
		if (SplitPos < 10)
		{
			SplitPos = 10;
		}
		if (SplitPos > (GetW() - 10)) {
			SplitPos = GetW() - 10;
		}

		Resized();


	}

	//SplitPos += mx;

}

