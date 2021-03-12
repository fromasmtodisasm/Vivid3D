#pragma once
#include "UIControl.h"
#include <vector>
#include "TreeItem.h"
#include "Texture2D.h"
#include "VerticalSrollerControl.h"
class TreeViewControl :
    public UIControl
{
public:

    TreeViewControl();

    TreeItem* AddItem(const char* text);
    void Render();
    int RenderNode(TreeItem* node,int x,int y);
    int CheckNode(TreeItem* node, int x, int y, int mx, int my);
    void SetRoot(TreeItem* node);
    void MouseMove(int x, int y, int dx, int dy);
    void MouseDown(int b);
    void AfterSet();
    void SetScroller();
    int GetTreeH(TreeItem* i,int y);
private:

    TreeItem* Root;
    int TreeY = 5;
    Texture2D* Bg;
    TreeItem* Over;
    TreeItem* Active;
    bool bd = false;
    VerticalScrollerControl* Scroller;
    int OffY = 0;

};

