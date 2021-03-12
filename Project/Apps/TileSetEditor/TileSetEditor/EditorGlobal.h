#pragma once
#include "TreeViewControl.h"
#include "MapEditControl.h"
#include "TileEditorControl.h"

class EditorGlobal
{
public:
	
	static TreeViewControl* SceneTree;
	static MapEditControl* MapEdit;
	static TileEditorControl* TileEd;

	static void RebuildSceneTree();


};

