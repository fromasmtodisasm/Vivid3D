#pragma once
#include "FrameBufferControl.h"
#include "SceneGraph.h"
#include "NodeCam.h"
#include "NodeLight.h"
#include "MeshLines.h"


enum EditMode {

	Translate,Rotate,Scale,Select

};

class EditorSceneView : public FrameBufferControl
{

public:

	EditorSceneView();
	void RenderBuffer(kFrameBuffer* pre);
	void RenderPreBuffer();
	void AfterSet();
	void MouseDown(int b);
	void MouseUp(int b);
	void MouseMove(int x, int y, int dx, int dy);
	//void KeyPressed(int key, bool shift);
	void KeyDown(int key);
	void KeyUp(int key);
	void SetMode(EditMode mode) {
		EdMode = mode;
		switch (mode) {
		case EditMode::Translate:
			gTranslate = gizmoTrans;
			break;
		case EditMode::Rotate:
			gTranslate = gizmoTrans;
			break;
		case EditMode::Scale:
			gTranslate = gizmoScale;
			break;
		}

		NodeBase* tX = gTranslate->FindNode("mX");
		tX->SetFlatCol(Vect3(1, 0, 0));
		NodeBase* tY = gTranslate->FindNode("mY");
		tY->SetFlatCol(Vect3(0, 1, 0));
		NodeBase* tZ = gTranslate->FindNode("mZ");
		tZ->SetFlatCol(Vect3(0, 0, 1));
		gTX = (NodeEntity*)tZ;
		gTY = (NodeEntity*)tY;
		gTZ = (NodeEntity*)tX;
		
		if (mode == EditMode::Scale) {
			gMid = (NodeEntity*)gTranslate->FindNode("mMid");
			gMid->SetFlatCol(Vect3(1, 0.7f, 0.f));
		}

	}
	EditMode GetMode() {
		return EdMode;
	}

	void SelectNode(NodeBase* node);
	void MoveNodeToCam();
	void MoveNodeInFront();

private:
	SceneGraph* ViewGraph = NULL;
	NodeCam* EditCam;
	float CamPitch, CamYaw;
	bool Rotating;
	float mX, mY, mZ;
	NodeLight* l1, * l2;
	MeshLines* EditGrid;
	MeshLines* EditSubGrid;
	NodeEntity* gizmoTrans, * gizmoRot, * gizmoScale;
	NodeEntity* gTranslate;
	NodeEntity* gTX;
	NodeEntity* gTY;
	NodeEntity* gTZ;
	NodeEntity* gMid;
	NodeEntity* gScale;
	NodeEntity* gRotate;
	bool pr = false;
//	NodeEntity* gScale;
	NodeEntity* ActiveNode;
	int mx, my;
	EditMode EdMode;
	bool Moving = false;
	bool Turning = false;
	bool Scaling = false;
	bool ShiftIn = false;
	bool MoveX, MoveY, MoveZ;
	bool MoveAll = false;

};

