#pragma once
#include "UIControl.h"
#include "Texture2D.h"
class VerticalScrollerControl :
    public UIControl
{
public:
    VerticalScrollerControl();
    void Render();
    int GetCur();
    void MouseDown(int b);
    void MouseUp(int b);
    void MouseMove(int mx, int my, int dx, int dy);
    void SetMax(int max) {
        Max = max;
    }
    void SetCur(int cur) {
        Cur = cur;
    }
    void SetChanged(std::function<void()> actOne)
    {
        changed = actOne;
    }
private:
    Texture2D* Img;
    int Max = 0;
    int RenderH = 0;
    int Cur = 0;
    int SY = 0;
    bool moveTo = false;
    std::function<void()> changed;
};

