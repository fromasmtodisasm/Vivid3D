#pragma once
#include <VerticalSplitterControl.h>
#include "SceneTreeView.h"
class SceneSplit :
    public VerticalSplitterControl
{
public:

    SceneSplit();

private:
    SceneTreeView* SceneTree;
};

