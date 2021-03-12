#pragma once
#include "HorizontalSplitterControl.h"
#include "SceneTreeView.h"
#include "EditorSecondSplit.h"
#include "SceneSplit.h"
class EditorMainSplit :
    public HorizontalSplitterControl
{
public:

    EditorMainSplit();
    void AfterSet();


private:


    EditorSecondSplit* Split2;
    SceneSplit* SceneS;

};

