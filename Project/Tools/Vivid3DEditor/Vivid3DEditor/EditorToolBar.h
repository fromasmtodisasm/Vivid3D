#pragma once
#include "ToolsControl.h"
class EditorToolBar :
    public ToolsControl
{
public:

    EditorToolBar();

private:
	ButtonControl* newScene;
		ButtonControl* loadScene;
		ButtonControl* saveScene;

		ButtonControl* select;
		ButtonControl * translate;
		ButtonControl * rotate;
		ButtonControl * scale;
};

