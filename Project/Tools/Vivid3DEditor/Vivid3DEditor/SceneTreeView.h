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
    void SelectNode(NodeBase* node);
    void SelectIf(NodeBase* node, TreeItem* item);
private:
    TreeItem* RootNode;
    SceneGraph* Graph;
};

