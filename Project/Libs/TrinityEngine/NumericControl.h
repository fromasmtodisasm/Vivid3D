#pragma once
#include "UIControl.h"
#include "ButtonControl.h"
#include "TextBoxControl.h"

class NumericControl :
    public UIControl
{
public:

    NumericControl();
    void Resized();
    void SetChanged(std::function<void(int num)> act) {
        actChanged = act;
    }
private:
    ButtonControl* Up = NULL;
    ButtonControl* Down = NULL;
    TextBoxControl* Num = NULL;
    int CNum = 0;
    std::function<void(int num)> actChanged;
};

