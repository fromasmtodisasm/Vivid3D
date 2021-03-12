#include "SceneSplit.h"
#include "Application.h"

SceneSplit::SceneSplit() {

	SetSplit(Application::WinH - 250);
	SceneTree = new SceneTreeView();
	SetTop(SceneTree);
}