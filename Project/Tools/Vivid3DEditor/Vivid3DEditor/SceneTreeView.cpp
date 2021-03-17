#include "SceneTreeView.h"
#include "EditorGlobal.h"

SceneTreeView::SceneTreeView() {

	Texture2D* iRoot = new Texture2D("edit/iroot.png", true, false);
	Texture2D* iNode = new Texture2D("edit/inode.png", true, false);

	RootNode = new TreeItem("Scene", iRoot);
	SetRoot(RootNode);

	auto actSelected = [&](TreeItem* item) {

		if (item == RootNode) {
			return;
		}
		EditorGlobal::SceneView->SelectNode((NodeBase*)item->DataObj);

	};

	SetItemSelected(actSelected);
	SetScroller();
	SetGraph(EditorGlobal::EditorGraph);
	EditorGlobal::SceneTree = this;
	Rebuild();

}

void SceneTreeView::SelectNode(NodeBase* node) {

	SelectIf(node, RootNode);

}

void SceneTreeView::SelectIf(NodeBase* node, TreeItem* item) {

	if (node == item->DataObj) {
		SetActiveItem(item);
	}

	for (int i = 0; i < item->Sub.size(); i++) {

		SelectIf(node, item->Sub[i]);

	}

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
	SetScroller();

}

void SceneTreeView::AddNodes(TreeItem* n, NodeBase* nb)
{
	const char* nn = nb->GetName();

	TreeItem* ni = new TreeItem(nn, NULL);

	ni->DataObj = (void*)nb;



	n->AddItem(ni);

	for (int i = 0; i < nb->NumSub(); i++) {

		AddNodes(ni, nb->GetSub(i));

	}

}