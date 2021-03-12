#include "EditorGlobal.h"
#include "strings.h"

TreeViewControl* EditorGlobal::SceneTree = NULL;
MapEditControl* EditorGlobal::MapEdit = NULL;
TileEditorControl* EditorGlobal::TileEd = NULL;

void EditorGlobal::RebuildSceneTree() {

	auto root = new TreeItem("Scene");

	auto lights = root->AddItem("Lights");

	auto l = MapEdit->GetMap()->GetLights();

	auto n = MapEdit->GetMap()->GetNodes();

	for (int i = 0; i < l.size(); i++) {

		const char* ln = "Light:";

		ln = strAddInt(ln, i);

		auto ni = lights->AddItem(ln);
		ni->DataInt = i;

		auto lAct = [&](TreeItem* i) {

			auto la = MapEdit->GetMap()->GetLights();
			auto al = la[i->DataInt];



			TileEd->SetLight(al);

		};

		ni->Act = lAct;

	}

	auto nodes = root->AddItem("Nodes");

	int nn = 0;

	for (int i = 0; i < n.size(); i++)
	{

		auto an = n[i];

		if (an->GetType() == NodeType::TypeNode)
		{

			

			const char* ln = an->GetName();

			//ln = strAddInt(ln, i);

			auto ni = nodes->AddItem(ln);
			ni->DataInt = i;

			auto lAct = [&](TreeItem* i) {

				auto la = MapEdit->GetMap()->GetNodes();
				auto al = la[i->DataInt];



				TileEd->SetNode(al);

			};

			ni->Act = lAct;

		}
	}

	SceneTree->SetRoot(root);




}