#include "EditorSceneView.h"
#include "IDraw.h"
#include "EditorGlobal.h"
#include "GLFW/glfw3.h"
#include "Application.h"
#include "ModelImport.h"

EditorSceneView::EditorSceneView() {

	ViewGraph = new SceneGraph();

	EditorGlobal::SceneView = this;
	EditorGlobal::EditorGraph = ViewGraph;
	EdMode = EditMode::Translate;

	EditCam = ViewGraph->GetCam();
	CamPitch = 0;
	CamYaw = 0;
	Rotating = false;
	mX = mY = mZ = 0;

	EditCam->SetPosition(0,6, 20);

	//CamPitch = 180.0f;
	//CamYaw = 180.0f;

	//EditCam->Rotate(180,0, 0);
	l1 = new NodeLight;
	l1->SetRange(1000);


	l1->SetPosition(0, -25, 30);
	ViewGraph->AddLight(l1);



	 l2 = new NodeLight;
	l2->SetRange(800);
	l2->SetDiffuse(Vect3(0, 2, 2));
	l2->SetPosition(0, 12, 20);
	ViewGraph->AddLight(l2);
	//l1 = l2;

	//EditCam->LookAt(0, 0, 0);

	//EditCam->SetPosition(0,
		//)

	EditGrid = new MeshLines();
	EditSubGrid = new MeshLines();

	for (int z = -100; z < 101; z = z + 1) {
		//for (int x = -100; x < 100; x = x + 1)
		//{

		EditSubGrid->AddLine(-100, 0, z, 100, 0, z);


		//}
	}
	for (int x = -100; x < 101; x = x + 1) {

		EditSubGrid->AddLine(x, 0, -100, x, 0, 100);

	}

	for (int z = -100; z < 101; z = z + 2) {
		//for (int x = -100; x < 100; x = x + 1)
		//{

		EditGrid->AddLine(-100, 0, z, 100, 0, z);


		//}
	}
	for (int x = -100; x < 101; x=x+2) {
		
		EditGrid->AddLine(x, 0, -100, x, 0, 100);

	}

	EditGrid->CreateVBO();
	EditSubGrid->CreateVBO();

	EditGrid->SetCol(Vect3(1, 1, 1));
	EditSubGrid->SetCol(Vect3(0,0.5f,0.5f));

	ViewGraph->AddLines(EditSubGrid);
	ViewGraph->AddLines(EditGrid);
	
	auto imp = new ModelImport;

	gTranslate = imp->ImportAI("c:\\content\\gizmo\\translate.fbx");

	//gTranslate->Rotate(0, 90, 0);


	NodeBase* tX = gTranslate->FindNode("mX");
	tX->SetFlatCol(Vect3(1, 0, 0));
	NodeBase* tY = gTranslate->FindNode("mY");
	tY->SetFlatCol(Vect3(0, 1, 0));
	NodeBase* tZ = gTranslate->FindNode("mZ");
	tZ->SetFlatCol(Vect3(0, 0, 1));
	gTX = (NodeEntity*)tZ;
	gTY = (NodeEntity*)tY;
	gTZ = (NodeEntity*)tX;

	gTranslate->SetScale(Vect3(0.02f, 0.02f, 0.02f));


}

void EditorSceneView::MouseDown(int b) {

	if (b == 1) {
		Rotating = true;
	}
	if (b == 0) {
		l2->RegenShadows();
		auto cp = EditCam->GetPosition();
		//cp.Z = -cp.Z;

		l1->SetPosition(cp);

		float x1, y1;

		//x1 = mx * Application::WinW;
		//y1 = my * Application::WinH;
		MoveX = false;
		MoveY = false;
		MoveZ = false;
		RayCastInfo gh = ViewGraph->CamPick(mx, my, GetW(), GetH(), gTranslate);
		if (gh.Hit) {
			if (ActiveNode != NULL) {

				printf("GIzmo hit!\n");
				if (gh.HitNode == gTY)
				{
					//Moving = true;

					MoveY = true;
				}
				if (gh.HitNode == gTX) {
					//Moving = true;
					MoveX = true;
				}
				if (gh.HitNode == gTZ) {
					//Moving = true;
					MoveZ = true;
				}
				if (EdMode == EditMode::Translate) {
					Moving = true;
					Turning = false;
				}
				else if (EdMode == EditMode::Rotate) {
					Turning = true;
					Moving = false;
				}
				return;
			}
		}
		else {

			printf("No hit.\n");
			Moving = false;

		}


		mx = mx - 25;
		my = my + 25;
		RayCastInfo inf = ViewGraph->CamPick(mx, my, GetW(), GetH());

		if (inf.Hit) {

			printf("Hit!\n");
			Vect3 hp = inf.HitNode->GetPosition();
			ActiveNode = (NodeEntity*)inf.HitNode;
			printf("Pos: X:%f Y:%f Z:%f\n", hp.X, hp.Y, hp.Z);
			glm::mat4 am = ActiveNode->GetWorld();
			glm::vec4 ap = am[3];
			gTranslate->SetPosition(ap.x, ap.y, ap.z);
		

		}
		else {

			ViewGraph->Debug();
			ActiveNode = NULL;
			printf("No hit\n");

		}


	}

}

void EditorSceneView::MouseUp(int b) {

	if (b == 1) {

		Rotating = false;

	}
	Moving = false;
}

void EditorSceneView::KeyDown(int key) {

	if (key == GLFW_KEY_W) {

		mZ = -1;

	}
	if (key == GLFW_KEY_SPACE) {
		pr = true;

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
	if (key == GLFW_KEY_SPACE) {
		pr = false;

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

	if (Moving) {

		if (MoveX) {

			ActiveNode->Move((float)(dx) * 0.1f , 0, 0);
			

		}
		if (MoveY) {
			ActiveNode->Move(0, (float)(dy) * 0.1f , 0);
		}
		if (MoveZ) {
			ActiveNode->Move(0, 0,(float)(dx)*0.1f);
		}
		glm::mat4 am = ActiveNode->GetWorld();
		glm::vec4 ap = am[3];
		gTranslate->SetPosition(ap.x, ap.y, ap.z);
		//gTranslate->SetRotation(ActiveNode->GetWorldRotation());
		return;
	}
	else if (Turning) {


		if (MoveX) {

			ActiveNode->Turn((float)(dx) * 0.1f, 0, 0);


		}
		if (MoveY) {
			ActiveNode->Turn(0, (float)(dy) * 0.1f, 0);
		}
		if (MoveZ) {
			ActiveNode->Turn(0, 0, (float)(dx) * 0.1f);
		}

	}

	if (Rotating) {
		CamPitch -= dy;
		CamYaw -= dx;
		
		//EditCam->Turn(dy, -dx, 0);
		printf("Pitch:%d Yaw:%d\n", (int)CamPitch, (int)CamYaw);

	
	}
	mx = x;
	my = y;

}

void EditorSceneView::AfterSet() {

	int w = GetW();
	int h = GetH();
	if (h == 0) return;
	EditCam->SetViewport(0, 0, w, h);

}

void EditorSceneView::RenderPreBuffer() {

	for (int i = 0; i < ViewGraph->NumLights(); i++) {

		auto l = ViewGraph->GetLight(i);
		l->DrawShadowMap(ViewGraph, ViewGraph->GetCam());

	}

}

void EditorSceneView::RenderBuffer(kFrameBuffer* b)
{


	EditCam->Move(mX*0.1f, mY*0.1f, mZ*0.1f);

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	if (pr) {

		l1->Test(5, EditCam, ViewGraph);
	}
	else {
		ViewGraph->Render();
	
		//ViewGraph->RenderDepth();
	}
	EditCam->Rotate(CamPitch, CamYaw, 0);

	if (ActiveNode != NULL) {
		glClear(GL_DEPTH_BUFFER_BIT);
		ViewGraph->RenderNodeFlat(gTranslate);
	}

	

	//Draw/->End


	//glClearColor(0.0f, 0, 0, 1.0f);

}