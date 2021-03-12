#pragma once
#include <TreeViewControl.h>
#include "SceneGraph.h"
class SceneTreeView :
    public TreeViewControl
{
public:
    SceneTreeView();
    void SetGraph(SceneGraph* graph);
    void Rebuild();
    void AddNodes(TreeItem* node, NodeBase* n);
private:
    TreeItem* RootNode;
    SceneGraph* Graph;
};

