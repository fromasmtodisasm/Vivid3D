#pragma once
#include "UIControl.h"
#include "Texture2D.h"
#include "ButtonControl.h"
class ToolsControl :
    public UIControl
{
public:
    ToolsControl();
    void Render();
    ButtonControl* AddItem(const char* name);
    void AddItem(UIControl*);
    void AddSeperator();
private:
    Texture2D* White;
    int IX = 0;
};

