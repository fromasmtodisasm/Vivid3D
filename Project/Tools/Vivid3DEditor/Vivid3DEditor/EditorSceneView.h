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
	}
	EditMode GetMode() {
		return EdMode;
	}

private:
	SceneGraph* ViewGraph = NULL;
	NodeCam* EditCam;
	float CamPitch, CamYaw;
	bool Rotating;
	float mX, mY, mZ;
	NodeLight* l1, * l2;
	MeshLines* EditGrid;
	MeshLines* EditSubGrid;
	NodeEntity* gTranslate;
	NodeEntity* gTX;
	NodeEntity* gTY;
	NodeEntity* gTZ;
	NodeEntity* gRotate;
	bool pr = false;
	NodeEntity* gScale;
	NodeEntity* ActiveNode;
	int mx, my;
	EditMode EdMode;
	bool Moving = false;
	bool Turning = false;
	bool Scaling = false;
	bool MoveX, MoveY, MoveZ;
};

