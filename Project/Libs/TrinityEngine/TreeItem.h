#pragma once
#include "UIControl.h"
#include "Texture2D.h"
class TreeItem :
    public UIControl
{
public:

    TreeItem();

    TreeItem(const char* text,Texture2D* icon=NULL) {

        SetText(text);
        Icon = icon;

    }

    TreeItem* AddItem(const char* text,Texture2D* icon = NULL) {

        auto ni = new TreeItem;

        ni->Icon = icon;
        ni->SetText(text);

        Sub.push_back(ni);

        return ni;

    }

    void AddItem(TreeItem* it) {

       

        Sub.push_back(it);
        

    }

    Texture2D* Icon;

    std::vector<TreeItem*> Sub;

    bool Open = true;

    std::function<void(TreeItem *)> Act = NULL;

    int DataInt;
    void* DataObj;

};

