#include "GUITestBed.h"
#include "UITheme.h"
#include "UITheme_Neon.h"
#include "MainMenuControl.h";
#include "FileRequestorControl.h"
#include "ImageControl.h"
#include "UI.h"

#include "Utils.h"
void GUITestBed::Init() {
	UITheme_Neon* theme = new UITheme_Neon();

	UI::SetTheme(theme);

	ui = new UI(Width(), Height());

	ButtonControl* b1 = new ButtonControl();
	ButtonControl* b2 = new ButtonControl();

	b2->Set(20, 200, 80, 30);
	b2->SetText("Test2\n");
	b1->Set(20, 35, 200, 30);
	b1->SetText("Test1\n");
	auto but_click = [&] {

		exit(0);

	};

	b1->SetAction(but_click);

	Texture2D* tex = new Texture2D("UI/BG/bg1.jpg",false);

	ImageControl *img = new ImageControl(tex);

	img->Set(0, 0, Width(), Height());

	WindowControl* w1 = new WindowControl();

	w1->Set(20, 20, 300, 350);
	//exit(0); 

	w1->SetText("Test Window\n");

	w1->AddBodyControl(b1);
	w1->AddBodyControl(b2);

	img->AddControl(w1);

	ui->GetRoot()->AddControl(img);

}

void GUITestBed::Update() {
	ui->Update();
}

void GUITestBed::Render() {

	ui->Render();

}