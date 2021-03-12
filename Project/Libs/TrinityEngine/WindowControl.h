#pragma once
#include "UIControl.h"
#include "VerticalSrollerControl.h"

class ButtonControl;

class WindowControl : public UIControl
{
public:

	WindowControl();

	void Render();

	void Resized();



	void AddBodyControl(UIControl* control) {
		Body->AddControl(control);
	}

protected:

	ButtonControl* Title;
	ButtonControl* Resize;
	UIControl* Body;
	VerticalScrollerControl* VScroller;
};

