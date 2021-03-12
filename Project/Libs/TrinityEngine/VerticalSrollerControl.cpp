#include "pch.h"
#include "VerticalSrollerControl.h"
#include "UI.h"

VerticalScrollerControl::VerticalScrollerControl() {

	Img = new Texture2D("UI/Neon/frame1.png",true);

}

void VerticalScrollerControl::MouseDown(int b) {
	moveTo = true;
}

void VerticalScrollerControl::MouseUp(int b) {

	moveTo = false;
}

void VerticalScrollerControl::MouseMove(int mx, int my, int dx, int dy) {

	if (Max< 0)
	{
		Max = 0;
	}

	float dh = (float)H / (float)Max;
	float ah = dh * (float)H;
	if (ah > H)
	{
		ah = H;
		return;
	}
	if (moveTo) {

		SY = SY + dy;
		if (SY < 0) SY = 0;
		if (SY > (H - ah))
		{
			SY = H - ah;
		}

		changed();

	};

}

void VerticalScrollerControl::Render() {

	float ah = 0;
	if (H > Max) {
		ah = GetH();
//		printf("H:%d Max:%d \n", H, Max);

	}
	else {

		float dh = (float)H / (float)Max;
	 ah = dh * (float)H;
		if (ah > H) ah = H;
	}
	UI::DrawTexture(Img, GetX(), GetY()+SY, GetW(), (int)ah, 1, 1, 1, 1);

}

int VerticalScrollerControl::GetCur() {

	float dh = (float)H / (float)Max;
	float ah = dh * (float)H;
	if (ah > H) ah = H;

	float SI = (float)(SY) / (float)(H - ah);

	float av = Max * SI;

	return (int)av;


	/*
	float dh = (float)H / (float)Max;
	float ah = dh * H;
	if (ah > H) ah = H;

	float bh = H - ah;
	float mi = Cur / bh;

	int v = (int)((float)Max * mi);
	if (v < 0) v = 0;
	if (v > H) v = H;
	*/
	//return v;

}
