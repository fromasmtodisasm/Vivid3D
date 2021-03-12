#include "EditorSceneView.h"
#include "IDraw.h"
#include "EditorGlobal.h"
#include "GLFW/glfw3.h"

EditorSceneView::EditorSceneView() {

	ViewGraph = new SceneGraph();

	EditorGlobal::SceneView = this;
	EditorGlobal::EditorGraph = ViewGraph;


	EditCam = ViewGraph->GetCam();
	CamPitch = 0;
	CamYaw = 0;
	Rotating = false;
	mX = mY = mZ = 0;

	EditCam->SetPosition(0, 10, -30);

	CamPitch = 180.0f;
	EditCam->Rotate(CamPitch, 0, 0);
	l1 = new NodeLight;
	l1->SetRange(500);

	l1->SetPosition(0, -10, 30);
	ViewGraph->AddLight(l1);



	NodeLight* l2 = new NodeLight;
	l2->SetRange(600);
	l2->SetDiffuse(Vect3(0, 2, 2));
	l2->SetPosition(0, -10, -85);
	ViewGraph->AddLight(l2);

	//EditCam->LookAt(0, 0, 0);

	//EditCam->SetPosition(0,
		//)



}

void EditorSceneView::MouseDown(int b) {

	if (b == 1) {
		Rotating = true;
	}
	if (b == 0) {

		auto cp = EditCam->GetPosition();
		cp.Z = -cp.Z;

		l1->SetPosition(cp);

	}

}

void EditorSceneView::MouseUp(int b) {

	if (b == 1) {

		Rotating = false;

	}

}

void EditorSceneView::KeyDown(int key) {

	if (key == GLFW_KEY_W) {

		mZ = -1;

	}
	if (key == GLFW_KEY_S) {
		mZ = 1;
	}
	if (key == GLFW_KEY_A) {
		mX = -1;
	}
	if (key == GLFW_KEY_D) {
		mX = 1;
	}

}

void EditorSceneView::KeyUp(int key) {
	if (key == GLFW_KEY_W) {

		mZ = 0;

	}
	if (key == GLFW_KEY_S) {
		mZ = 0;
	}
	if (key == GLFW_KEY_A) {
		mX = 0;
	}
	if (key == GLFW_KEY_D) {
		mX = 0;
	}
}

void EditorSceneView::MouseMove(int x,int y,int dx,int dy) {

	if (Rotating) {
		CamPitch += dy;
		CamYaw += dx;
		
		//EditCam->Turn(dy, -dx, 0);
		printf("Pitch:%d Yaw:%d\n", (int)CamPitch, (int)CamYaw);
		EditCam->Rotate(CamPitch, CamYaw, 0);
	
	}


}

void EditorSceneView::AfterSet() {

	int w = GetW();
	int h = GetH();
	if (h == 0) return;
	EditCam->SetViewport(0, 0, w, h);

}

void EditorSceneView::RenderBuffer(kFrameBuffer* b)
{


	EditCam->Move(mX, mY, mZ);

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	ViewGraph->Render();


	//Draw/->End


	//glClearColor(0.0f, 0, 0, 1.0f);

}