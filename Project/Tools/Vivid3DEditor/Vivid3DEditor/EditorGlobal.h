#pragma once
#include "EditorSceneView.h"
#include "SceneGraph.h"
#include "SceneTreeView.h"
class EditorGlobal
{
public:
	static EditorSceneView* SceneView;
	static SceneGraph* EditorGraph;
	static SceneTreeView* SceneTree;
};

