#pragma once
#include "NodeBase.h"
#include "NodeEntity.h"
#include "FXMesh3D.h"
#include "NodeCam.h"
#include "NodeLight.h"

class SceneGraph
{
public:
	
	SceneGraph();
	void AddEntity(NodeEntity* ent);
	void AddLight(NodeLight* light);
	NodeEntity* GetEntity(int id);
	int NumEntity();
	NodeCam* GetCam();
	void SetCam(NodeCam* cam);
	void Render();
	void RenderNode(NodeEntity* node);
	NodeBase* GetRoot() {
		return Root;
	}
private:

	FXMesh3D* FXMesh;

	NodeBase* Root = NULL;

	std::vector<NodeLight*> Lights;

	NodeCam* Cam;

};

