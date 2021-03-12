#pragma once
#include "UIControl.h"

class HorizontalSplitterControl : public UIControl
{
public:

	void SetLeft(UIControl* control) {

		Left = control;
		Resized();
		AddControl(control);

	};

	void SetRight(UIControl* control) {

		Right = control;
		Resized();
		AddControl(control);

	}

	int GetLeftW() {

		return SplitPos - 5;
	}

	int GetRightW() {
		return W - SplitPos - 5;
	}

	void SetSplit(int split) {
		SplitPos = split;
		Resized();
	}

	void MouseDown(int b);
	void MouseUp(int b);
	void MouseMove(int x, int y, int dx, int dy);

	void Resized();

	void Render();

	int GetSplit() {

		return SplitPos;
	}

private:

	int SplitPos = -1;
	UIControl* Left = NULL;
	UIControl* Right = NULL;
	bool Dragging = false;
	bool OverDrag = false;
};

