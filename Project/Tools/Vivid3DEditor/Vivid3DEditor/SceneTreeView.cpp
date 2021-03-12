#include "SceneTreeView.h"
#include "EditorGlobal.h"

SceneTreeView::SceneTreeView() {

	Texture2D* iRoot = new Texture2D("edit/iroot.png", true, false);
	Texture2D* iNode = new Texture2D("edit/inode.png", true, false);

	RootNode = new TreeItem("Scene", iRoot);
	SetRoot(RootNode);

	
	SetScroller();
	SetGraph(EditorGlobal::EditorGraph);
	EditorGlobal::SceneTree = this;
	Rebuild();

}

void SceneTreeView::SetGraph(SceneGraph* graph) {
	Graph = graph;
}

void SceneTreeView::Rebuild() {

	Texture2D* iRoot = new Texture2D("edit/iroot.png", true, false);
	Texture2D* iNode = new Texture2D("edit/inode.png", true, false);

	RootNode = new TreeItem("Scene", iRoot);
	SetRoot(RootNode);

	AddNodes(RootNode, Graph->GetRoot());

}

void SceneTreeView::AddNodes(TreeItem* n, NodeBase* nb)
{
	const char* nn = nb->GetName();

	TreeItem* ni = new TreeItem(nn, NULL);

	n->AddItem(ni);

	for (int i = 0; i < nb->NumSub(); i++) {

		AddNodes(ni, nb->GetSub(i));

	}

}