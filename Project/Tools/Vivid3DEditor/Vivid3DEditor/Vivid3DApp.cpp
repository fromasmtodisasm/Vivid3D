#include "Vivid3DApp.h"
#include "UITheme_Neon.h"


Vivid3DApp::Vivid3DApp()
{

}

Vivid3DApp* Vivid3DApp::Main = NULL;

void Vivid3DApp::InitUI() {

	Main = this;
	


}

void Vivid3DApp::Init() {

	Main = this;

	InitUI();

}

void Vivid3DApp::Update() {


}

void Vivid3DApp::Render() {


}