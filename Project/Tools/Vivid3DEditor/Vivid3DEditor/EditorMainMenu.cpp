#include "EditorMainMenu.h"
#include "Application.h"
#include "Texture2D.h"

void EditorMainMenu::SetupProjectMenu() {

	Texture2D* tNewProj = new Texture2D("edit/iNewProj.png", true, false);
	Texture2D* tLoadProj = new Texture2D("edit/iLoadProj.png", true, false);
	Texture2D* tSaveProj = new Texture2D("edit/iSaveProj.png", true, false);
	Texture2D* tCloseProj = new Texture2D("edit/iCloseProj.png", true, false);
	Texture2D* tExit = new Texture2D("edit/iExit.png", true, false);
	Texture2D* tProj = new Texture2D("edit/iProj.png", true, false);
	Texture2D* tScene = new Texture2D("edit/iScene.png", true, false);
	Texture2D* tScript = new Texture2D("edit/iScript.png", true, false);

	Project = AddItem("Project");
	ProjNew = Project->AddItem("New",tNewProj);
	
	NewProj = ProjNew->AddItem("Project",tProj);
	NewScene = ProjNew->AddItem("Scene",tScene);
	NewScript = ProjNew->AddItem("Script",tScript);

	Project->AddSeperator();

	ProjLoad = Project->AddItem("Load Project",tLoadProj);
	ProjSave = Project->AddItem("Save Project",tSaveProj);
	ProjClose = Project->AddItem("Close Project",tCloseProj);
	ProjExit = Project->AddItem("Exit Vivid3D",tExit);

	auto aExit = [&] {

		exit(1);

	};

	ProjExit->SetAction(aExit);

}

void EditorMainMenu::SetupEditMenu() {

	Texture2D* iCopy = new Texture2D("Edit/iCopy.png", true, false);
	Texture2D* iCut = new Texture2D("edit/iCut.png", true, false);
	Texture2D* iPaste = new Texture2D("edit/iPaste.png", true, false);
	Texture2D* iDelete = new Texture2D("edit/iDelete.png", true, false);

	Edit = AddItem("Edit");

	EditCopy = Edit->AddItem("Copy",iCopy);
	EditCut = Edit->AddItem("Cut",iCut);
	Edit->AddSeperator();
	EditPaste= Edit->AddItem("Paste",iPaste);
	Edit->AddSeperator();
	EditDelete = Edit->AddItem("Delete",iDelete);





}

void EditorMainMenu::SetupAddMenu() {

	Add = AddItem("Add");

}

void EditorMainMenu::SetupSettingsMenu() {

	Settings = AddItem("Settings");

}

void EditorMainMenu::SetupToolsMenu() {

	Tools = AddItem("Tools");

}


EditorMainMenu::EditorMainMenu() {

	
	SetupProjectMenu();
	SetupEditMenu();
	SetupAddMenu();
	SetupSettingsMenu();
	SetupToolsMenu();
	





	
	Set(20, 0, Application::WinW, 25);


}