#pragma once
#include "Application.h"
#include "UI.h"

class Vivid3DApp :
    public Application
{
public:
    Vivid3DApp();

    void Init();
    void Update();
    void Render();
    void InitUI();

    static Vivid3DApp* Main;

private:

    UI* ui;
   

};

