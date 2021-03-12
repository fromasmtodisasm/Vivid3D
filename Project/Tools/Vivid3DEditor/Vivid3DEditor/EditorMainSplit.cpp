#include "EditorMainSplit.h"

EditorMainSplit::EditorMainSplit() {

	

	SetSplit(230);

	Split2 = new EditorSecondSplit();

	SceneS = new SceneSplit;

	SetLeft(SceneS);
	SetRight(Split2);

}

void EditorMainSplit::AfterSet() {



}