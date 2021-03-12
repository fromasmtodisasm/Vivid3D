#pragma once
#include "EditorSceneView.h"
#include <HorizontalSplitterControl.h>
class EditorThirdSplit :
    public HorizontalSplitterControl
{
public:

    EditorThirdSplit();

private:
    EditorSceneView* View;


};

