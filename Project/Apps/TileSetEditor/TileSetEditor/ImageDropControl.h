#pragma once
#include <ImageControl.h>
class ImageDropControl :
    public ImageControl
{
public:
    ImageDropControl(Texture2D* img);
    void Drop(UIControl* drop);
};

