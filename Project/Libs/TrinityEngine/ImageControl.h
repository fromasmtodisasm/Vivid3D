#pragma once
#include "UIControl.h"

class Texture2D;

class ImageControl : public UIControl
{
public:

	ImageControl() {};
	ImageControl(Texture2D* img);
	ImageControl(const char* path,bool alpha);

	void Render();


protected:

	Texture2D* Image;

};

