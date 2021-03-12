#include "EditorThirdSplit.h"
#include "Application.h"

EditorThirdSplit::EditorThirdSplit() {

	SetSplit(Application::WinW-500);

	View = new EditorSceneView;

	SetLeft(View);

}