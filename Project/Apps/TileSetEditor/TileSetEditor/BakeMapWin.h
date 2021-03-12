#pragma once
#include "UI.h"
#include "TextBoxControl.h"
#include "ButtonControl.h"
#include "WindowControl.h"
class BakeMapWin : public WindowControl
{
public:

	BakeMapWin();
	void Resized();

private:
	TextBoxControl* tbWidth;
	TextBoxControl* tbHeight;
	TextBoxControl* tbBlur;
	ButtonControl* bBake;

};

