#pragma once

#include "MainMenuControl.h"

class EditorMainMenu :
    public MainMenuControl
{
public:

    EditorMainMenu();
    void SetupProjectMenu();
    void SetupEditMenu();
    void SetupAddMenu();
    void SetupSettingsMenu();
    void SetupToolsMenu();
 
private:

    //Project
    MenuItem* Project;
    MenuItem* ProjNew;

    MenuItem* NewProj;
    MenuItem* NewScene;
    MenuItem* NewScript;

    MenuItem* ProjLoad;
    MenuItem* ProjSave;
    MenuItem* ProjClose;
    MenuItem* ProjExit;

    //Edit
    MenuItem* Edit;

    MenuItem* EditCopy;
    MenuItem* EditCut;
    MenuItem* EditPaste;
    MenuItem* EditDelete;
    MenuItem* EditMoveHere;
    MenuItem* EditMoveInFront;
    MenuItem* EditMoveCameraToNode;

    
    //Add
    MenuItem* Add;
    
    //Settings
    MenuItem* Settings;
    
    //Tools
    MenuItem* Tools;

};

