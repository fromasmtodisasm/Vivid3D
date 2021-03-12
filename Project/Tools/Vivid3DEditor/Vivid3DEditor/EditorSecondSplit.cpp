#include "EditorSecondSplit.h"
#include "Application.h"

EditorSecondSplit::EditorSecondSplit(){

	ContentPath = "c:\\content\\";

	SetSplit(Application::WinH - 250);

	ThirdSplit = new EditorThirdSplit;

	SetTop(ThirdSplit);

	Browser = new EditorContentBrowser;

	SetBottom(Browser);

	Browser->ScanDir(ContentPath);

}

const char* EditorSecondSplit::ContentPath = "";
