#pragma once
#include "FrameBufferControl.h"
#include "SceneGraph.h"
#include "NodeCam.h"
#include "NodeLight.h"
class EditorSceneView : public FrameBufferControl
{

public:

	EditorSceneView();
	void RenderBuffer(kFrameBuffer* pre);
	void AfterSet();
	void MouseDown(int b);
	void MouseUp(int b);
	void MouseMove(int x, int y, int dx, int dy);
	//void KeyPressed(int key, bool shift);
	void KeyDown(int key);
	void KeyUp(int key);

private:
	SceneGraph* ViewGraph = NULL;
	NodeCam* EditCam;
	float CamPitch, CamYaw;
	bool Rotating;
	float mX, mY, mZ;
	NodeLight* l1;
};

