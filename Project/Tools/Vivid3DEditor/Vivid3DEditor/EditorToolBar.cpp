#include "EditorToolBar.h"
#include "ButtonControl.h"
EditorToolBar::EditorToolBar() {

	Texture2D* iNewProj = new Texture2D("edit/iNewProj.png", true, false);
	Texture2D* iLoadScene = new Texture2D("edit/iLoadProj.png", true, false);
	Texture2D* iSaveScene = new Texture2D("edit/iSaveProj.png", true, false);
	Texture2D* iMove = new Texture2D("edit/iMove.png", true, false);
	Texture2D* iRotate = new Texture2D("edit/iRotate.png", true, false);
	Texture2D* iScale = new Texture2D("edit/iScale.png", true, false);
	Texture2D* iSelect = new Texture2D("edit/iSelect2.png", true, false);
	Texture2D* iPlay = new Texture2D("edit/iPlay2.png", true, false);
	Texture2D* iStop = new Texture2D("edit/iStop2.png", true, false);
	Texture2D* iPause = new Texture2D("edit/iPause.png", true, false);

	ButtonControl* newScene = new ButtonControl();
	ButtonControl* loadScene = new ButtonControl();
	ButtonControl* saveScene = new ButtonControl();
	
	ButtonControl* select = new ButtonControl();
	ButtonControl* translate = new ButtonControl();
	ButtonControl* rotate = new ButtonControl();
	ButtonControl* scale = new ButtonControl();

	ButtonControl* play = new ButtonControl();
	ButtonControl* pause = new ButtonControl();
	ButtonControl* stop = new ButtonControl();


	newScene->SetIcon(iNewProj);
	loadScene->SetIcon(iLoadScene);
	saveScene->SetIcon(iSaveScene);
	translate->SetIcon(iMove);
	rotate->SetIcon(iRotate);
	scale->SetIcon(iScale);
	select->SetIcon(iSelect);
	play->SetIcon(iPlay);
	stop->SetIcon(iStop);
	pause->SetIcon(iPause);
	newScene->SetText("New");
	loadScene->SetText("New");
	saveScene->SetText("New");
	translate->SetText("New");
	rotate->SetText("New");
	scale->SetText("New");
	select->SetText("New");
	play->SetText("New");
	pause->SetText("New");
	stop->SetText("New");


	select->SetToolTip("Select node mode.");
	newScene->SetToolTip("Creates a new project.");
	loadScene->SetToolTip("Loads a different project.");
	saveScene->SetToolTip("Saves the current project.");
	translate->SetToolTip("Translate the current 3D node.");
	rotate->SetToolTip("Rotate the current 3D node.");
	scale->SetToolTip("Scale the current 3D node.");
	play->SetToolTip("Begin the current application.");
	stop->SetToolTip("Stop the current application.");
	pause->SetToolTip("Pause and break the current application.");
	/// Application-Wide search feature. using a search class.





	AddItem(newScene);
	AddItem(loadScene);
	AddItem(saveScene);
	AddSeperator();
	AddItem(select);
	AddSeperator();
	AddItem(translate);
	AddItem(rotate);
	AddItem(scale);
	AddSeperator();
	AddItem(play);
	AddItem(stop);
	AddItem(pause);
	AddSeperator();

};