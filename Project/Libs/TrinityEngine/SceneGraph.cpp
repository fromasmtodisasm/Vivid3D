#include "pch.h"
#include "SceneGraph.h"

SceneGraph::SceneGraph() {

	Root = new NodeBase();
	FXMesh = new FXMesh3D;
	Cam = new NodeCam;
	Lights.resize(0);
	//while(true){}

}

void SceneGraph::AddLight(NodeLight* light) {

	Lights.push_back(light);

}

void SceneGraph::AddEntity(NodeEntity* node) {

	Root->Add(node);

}

void SceneGraph::RenderNode(NodeEntity* node) {

	//node->Rotate(180, 0, 0);

	FXMesh->mProj = Cam->GetProj();
	FXMesh->mModel = node->GetWorld();
	FXMesh->mView = Cam->GetWorld();
	
	FXMesh->Cam = Cam;
	bool first = true;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);

	for (int i = 0; i < Lights.size(); i++) {
		FXMesh->Light = Lights[i];
		FXMesh->bind();
		node->Render();
		FXMesh->unbind();
		if (first) {
			glBlendFunc(GL_ONE, GL_ONE);
		}
		//glDisable(GL_DEPTH_TEST)

	}

	for (int i = 0; i < node->NumSub(); i++) {

		RenderNode((NodeEntity*)node->GetSub(i));

	}
}

void SceneGraph::Render() {

	for (int i = 0; i < Root->NumSub(); i++) {

		RenderNode((NodeEntity*)Root->GetSub(i));

	}

}

void SceneGraph::SetCam(NodeCam* cam) {
	Cam = cam;
}

NodeCam* SceneGraph::GetCam() {

	return Cam;

}