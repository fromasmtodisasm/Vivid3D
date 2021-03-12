#pragma once
#include <AppState.h>
#include "UI.h"
#include "MainMenuControl.h"
#include "EditorMainMenu.h"
#include "EditorToolBar.h"
#include "EditorMainSplit.h"
class MainEditorState :
    public AppState
{

public:

    void InitUI();
    void Init();
    void Update();
    void Render();
    void Resized(int w, int h);

    static MainEditorState* Main;

private:

    UI* ui;
  //  EditorMainMenu* MainMenu;
    EditorMainMenu* Menu;
    EditorToolBar* Toolbar;
    EditorMainSplit* MainSplit;

};

