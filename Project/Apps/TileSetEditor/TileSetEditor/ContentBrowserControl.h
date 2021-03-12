#pragma once
#include "WindowControl.h"
#include "ContentItem.h"
#include <vector>
#include <stack>

class ContentBrowserControl :
    public UIControl
{
public:

    void ScanDir(const char* path);
    void MouseDown(int b);
    void Render();
private:
   std::vector<ContentItem*> Items;
   std::stack<const char*> paths;
};


