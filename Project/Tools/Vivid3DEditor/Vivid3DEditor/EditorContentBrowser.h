#pragma once
#include <UIControl.h>
#include "ContentItem.h"
#include "Texture2D.h"
#include <stack>
#include "VerticalSrollerControl.h"
class EditorContentBrowser :
    public UIControl
{
public:
    EditorContentBrowser();

    void Render();
    void MouseMove(int x, int y, int mx, int my);
    void ScanDir(const char* path);
    void DoubleClick(int b);
    void MouseDown(int b);
    void SetScroller();
    void AfterSet();

private:
    std::vector<ContentItem*> Items;
    Texture2D* iFolder;
    Texture2D* iFile;
    ContentItem* OverItem;
    ContentItem* ActiveItem;
    std::stack<const char*> paths;
    VerticalScrollerControl* Scroller;
    int OffY = 0;
    int MaxY = 0;
};

