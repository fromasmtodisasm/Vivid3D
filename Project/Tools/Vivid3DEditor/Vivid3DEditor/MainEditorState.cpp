#include "MainEditorState.h"
#include "UITheme_Neon.h"
#include "Application.h"

MainEditorState* MainEditorState::Main = NULL;

void MainEditorState::InitUI() {

	Main = this;
	const char* ContentPath = "C:/Projects";

	UITheme_Neon* theme = new UITheme_Neon();

	UI::SetTheme(theme);

	ui = new UI(Application::WinW, Application::WinH);

	Menu = new EditorMainMenu;
	Toolbar = new EditorToolBar;
	MainSplit = new EditorMainSplit;


	ui->GetRoot()->AddControl(Toolbar);
	ui->GetRoot()->AddControl(MainSplit);
	ui->GetRoot()->AddControl(Menu);

	//ui->SetMenu(Menu);

	Resized(Application::WinW, Application::WinH);

}

void MainEditorState::Resized(int w, int h) {

	Menu->Set(20, 0, Application::WinW, 25);
	Toolbar->Set(0, 26, Application::WinW, 37);
	MainSplit->Set(0, 65, Application::WinW, Application::WinH - 60);

}

void MainEditorState::Init() {

	InitUI();



}

void MainEditorState::Update() {

	ui->Update();

}

void MainEditorState::Render() {


	ui->Render();

}