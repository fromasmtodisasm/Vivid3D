#pragma once
#include "VString.h"
#include "Texture2D.h"
#include "UIControl.h"
class TextBoxControl :
    public UIControl
{
public:
    TextBoxControl();
    void Render();
    void Update();
    void SetChanged(std::function<void(TextBoxControl* tb, VString txt)> act) {
        TextChanged = act;
    }
    void SetActive(bool act) {

        Active = act;
        if (act) {
            
            caratX = VString(GetText()).Len();
        }

    }
    void KeyPressed(int key,bool shift);
private:
    Texture2D* Bg;
    int lastCarat=0;
    bool caratOn = true;
    VString Txt;
    int caratX = 0;
    std::function<void(TextBoxControl * tb,VString t)> TextChanged= NULL;
};



