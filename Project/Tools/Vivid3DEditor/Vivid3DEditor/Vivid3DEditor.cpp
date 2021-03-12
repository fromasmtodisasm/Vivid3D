// Vivid3DEditor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include "Vivid3DApp.h"
#include <stdio.h> 
#include "MainEditorState.h"

int main()
{
    Application::ContentPath = "C:\\Git\\Vivid3DCPP\\Project\\Libs\\TrinityEngine\\x64\\Debug\\Data\\";

    const char* test = Application::GetPath("Edit/highlight1.png");


    std::cout << "Starting Vivid3D editor.\n";

    Vivid3DApp* app = new Vivid3DApp();
    Application::InitialState = new MainEditorState;
    app->CrWindow(1650, 868, "Vivid3D Editor (c)Vivid Games 2021");
    app->SetFileSystem(Application::ContentPath);
    app->Run();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
