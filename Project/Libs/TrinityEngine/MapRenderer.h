#pragma once
#include "Map.h"
#include "kEffect.h"
#include "glm/glm.hpp"
#include <glm/ext.hpp>
#include "IDraw.h"
#include "SimpleMath.h"
class MapRenderer
{
public:
	MapRenderer(Map* map) {

		Draw = new IDraw(Application::WinW, Application::WinH);
		Map = map;
		stage1 = NULL;
		stage2 = NULL;
		stage3 = NULL;
		stage4 = NULL;

		WhiteShadow = new Texture2D("edit/white1.png", false, false);

		MapMesh = new Mesh2D();
		MapMesh2 = new Mesh2D();

		MapW = Map->MapW;
		MapH = Map->MapH;
		TileW = Map->TileW;
		TileH = Map->TileH;

		float ox = (MapW * TileW) / 2;
		float oy = (MapH * TileH) / 2;

		ox = -ox;
		oy = -oy;

		float mapW = Map->GetW();
		float mapH = Map->GetH();

		for (int z = 0; z < 6; z++) {
			for (int y = 0; y < MapH; y++) {
				for (int x = 0; x < MapW; x++) {


					float tx, ty;

					tx = x * TileW;
					ty = y * TileH;
					float rx = tx;
					float ry = ty;
					tx = tx + ox;
					ty = ty + oy;


					MapTile* tile = Map->Tiles[x][y][z];

					if (tile != NULL) {

						if (tile->GetCastsShadow()) {

							//ShadowMesh->AddQuad(tx, ty, TileW, TileH, tile->GetImage(), tile->GetNormal(), 1, 1, 1, 1);

						}

						float u1;
						float v1;
						float u2;
						float v2;

						u1 = rx / mapW;
						u2 = (rx + TileW) / mapW;
						v1 = ry / mapH;
						v2 = (ry + TileH) / mapH;
						printf("U1:%f V1:%f\n", u1, v1);
						//u1 = u1 * 2;
						//v1 = v1 * 2;
						//u2 = u2 * 2;
						//v2 = v2 * 2;


						//CompiledMesh->AddQuad(tx, ty, TileW, TileH, tile->GetImage(), tile->GetNormal(), 1, 1, 1, 1);
						MapMesh->AddQuadLM(tx, ty, TileW, TileH, u1, v1, u2, v2, tile->GetImage(), tile->GetNormal(), 1, 1, 1, 1);
						MapMesh2->AddQuad(tx, ty, TileW, TileH, tile->GetImage(), tile->GetNormal(), 1, 1, 1, 1);

					}


				}
			}
		}

		MapMesh->CompileLM();
		MapMesh2->Compile();
	}

	void Stage3() {

		glClear(GL_DEPTH_BUFFER_BIT);

		glBlendFunc(GL_ONE, GL_ZERO);

		Draw->Begin();

		for (int i = 0; i < Map->Decals.size(); i++) {

			auto d = Map->Decals[i];
			float tW, tH;

			tW = TileW * Map->CamZ;
			tH = TileH * Map->CamZ;

			int sW = Application::WinW;
			int sH = Application::WinH;

			int lw, lh;
			lw = d->GetWidth();
			lh = d->GetHeight();
			lw = lw * Map->CamZ;
			lh = lh * Map->CamZ;

			auto pos = d->GetPos();

			float ren_x = pos.X - Map->CamX;
			float ren_y = pos.Y - Map->CamY;

			float nx = ren_x - Application::WinW / 2;
			float ny = ren_y - Application::WinH / 2;

			Vec2 cp(nx, ny);

			float rot = Map->CamRot + d->GetRot();

			rot = rot + 90.0f + 180.0f;

			cp = rotatePoint(cp, Map->CamRot);

			cp.X *= Map->CamZ;
			cp.Y *= Map->CamZ;

			ren_x = cp.X + (Application::WinW / 2);
			ren_y = cp.Y + (Application::WinH / 2);



			float tw, th;

			tw = tW;
			th = tH;

			float* tx = (float*)malloc(4 * 4); //new float[4];
			float* ty = (float*)malloc(4 * 4); //new float[4];

			float ax, ay;

			ax = -(lw / 2);
			ay = -(lh / 2);

			Vec2 p1, p2, p3, p4;

			p1.X = ax;
			p1.Y = ay;
			p2.X = -ax;
			p2.Y = ay;
			p3.X = -ax;
			p3.Y = -ay;
			p4.X = ax;
			p4.Y = -ay;

			p1 = rotatePoint(p1, rot);
			p2 = rotatePoint(p2, rot);
			p3 = rotatePoint(p3, rot);
			p4 = rotatePoint(p4, rot);

			p1 = vecAdd(p1, ren_x, ren_y);
			p2 = vecAdd(p2, ren_x, ren_y);
			p3 = vecAdd(p3, ren_x, ren_y);
			p4 = vecAdd(p4, ren_x, ren_y);



			tx[0] = p1.X;
			tx[1] = p2.X;
			tx[2] = p3.X;
			tx[3] = p4.X;

			ty[0] = p1.Y;
			ty[1] = p2.Y;
			ty[2] = p3.Y;
			ty[3] = p4.Y;

			Draw->DrawTexCoords(tx, ty, d->GetDecalTex(), d->GetDecalTex(), 1, 1, 1, 1);
			//UI::RenderText(tx[1], ty[1], s->GetDebugStr(), 1, 1, 1, 1, Draw);
			free(tx);

			free(ty);
		}

		stage3->bind();
		stage3->setInt("tR", 0);
		stage3->setInt("sW", Application::WinW);
		stage3->setInt("sH", Application::WinH);
		stage3->setInt("tS", 1);
		stage3->setInt("noLight", 1);
		stage3->setMat("proj", proj);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (int i = 0; i < Map->Lights.size(); i++) {

			auto l1 = Map->Lights[i];


			//l1->SetDiffuse(Vec3(1, 0, 0));



			auto pos = l1->GetPos();

			float ren_x = pos.X - Map->CamX;
			float ren_y = pos.Y - Map->CamY;

			float nx = ren_x - Application::WinW / 2;
			float ny = ren_y - Application::WinH / 2;

			Vec2 cp(nx, ny);

			cp = rotatePoint(cp, Map->CamRot);

			cp.X *= Map->CamZ;
			cp.Y *= Map->CamZ;

			ren_x = cp.X + (Application::WinW / 2);
			ren_y = cp.Y + (Application::WinH / 2);
			l1->SetRender(ren_x, ren_y, 1, l1->GetRange() * Map->CamZ);

			Vec3 nlp = l1->GetRPos();
			Vec3 ldif = l1->GetDiffuse();

			stage3->setVec3("lightPos", nlp.X, nlp.Y, 1.0f);
			stage3->setVec3("lightDiff", ldif.X, ldif.Y, ldif.Z);
			stage3->setFloat("lightRange", l1->GetRRange());

			if (l1->HasSB()) {
				l1->GetSB()->GetBB()->Bind(1);
				stage3->setInt("noShadows", 0);
			}
			else {
				stage3->setInt("noShadows", 1);
			}
			Draw->End(false);

			if (l1->HasSB()) {
				l1->GetSB()->GetBB()->Release(1);
			}
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			glClear(GL_DEPTH_BUFFER_BIT);
		}

		stage3->unbind();

		//Draw->End();

		Draw->Begin();

		for (int i = 0; i < Map->Nodes.size(); i++) {

			auto s = Map->Nodes[i];

			if (s->GetType() == NodeType::TypeLight) {
				continue;
			}

			float tW, tH;

			tW = Map->TileW * Map->CamZ;
			tH = Map->TileH * Map->CamZ;

			int sW = Application::WinW;
			int sH = Application::WinH;

			int lw, lh;
			lw = s->GetW();
			lh = s->GetH();
			lw = lw * Map->CamZ;
			lh = lh * Map->CamZ;

			auto pos = s->GetPos();

			float ren_x = pos.X - Map->CamX;
			float ren_y = pos.Y - Map->CamY;

			float nx = ren_x - Application::WinW / 2;
			float ny = ren_y - Application::WinH / 2;

			Vec2 cp(nx, ny);

			float rot = Map->CamRot + s->GetRot()+90;

			rot = rot + 90.0f + 180.0f;

			cp = rotatePoint(cp, Map->CamRot);

			cp.X *= Map->CamZ;
			cp.Y *= Map->CamZ;

			ren_x = cp.X + (Application::WinW / 2);
			ren_y = cp.Y + (Application::WinH / 2);

			float tw, th;

			tw = tW;
			th = tH;

			float* tx = (float*)malloc(4 * 4); //new float[4];
			float* ty = (float*)malloc(4 * 4); //new float[4];

			float ax, ay;

			ax = -(lw / 2);
			ay = -(lh / 2);

			Vec2 p1, p2, p3, p4;

			p1.X = ax;
			p1.Y = ay;
			p2.X = -ax;
			p2.Y = ay;
			p3.X = -ax;
			p3.Y = -ay;
			p4.X = ax;
			p4.Y = -ay;

			p1 = rotatePoint(p1, rot);
			p2 = rotatePoint(p2, rot);
			p3 = rotatePoint(p3, rot);
			p4 = rotatePoint(p4, rot);

			p1 = vecAdd(p1, ren_x, ren_y);
			p2 = vecAdd(p2, ren_x, ren_y);
			p3 = vecAdd(p3, ren_x, ren_y);
			p4 = vecAdd(p4, ren_x, ren_y);



			tx[0] = p1.X;
			tx[1] = p2.X;
			tx[2] = p3.X;
			tx[3] = p4.X;

			ty[0] = p1.Y;
			ty[1] = p2.Y;
			ty[2] = p3.Y;
			ty[3] = p4.Y;

			Draw->DrawTexCoords(tx, ty, s->GetImage(), s->GetImage(), 1, 1, 1, 1);
			//			UI::RenderText(tx[1], ty[1], s->GetDebugStr(), 1, 1, 1, 1, Draw);

			free(tx);
			free(ty);



		}

		for (int i = 0; i < Map->Sprites.size(); i++) {

			auto s = Map->Sprites[i];

			float tW, tH;

			tW = Map->TileW * Map->CamZ;
			tH = Map->TileH * Map->CamZ;

			int sW = Application::WinW;
			int sH = Application::WinH;

			int lw, lh;
			lw = s->GetWidth();
			lh = s->GetHeight();
			lw = lw * Map->CamZ;
			lh = lh * Map->CamZ;

			auto pos = s->GetPos();

			float ren_x = pos.X - Map->CamX;
			float ren_y = pos.Y - Map->CamY;

			float nx = ren_x - Application::WinW / 2;
			float ny = ren_y - Application::WinH / 2;

			Vec2 cp(nx, ny);

			float rot = Map->CamRot + s->GetRot();

			rot = rot + 90.0f + 180.0f;

			cp = rotatePoint(cp, Map->CamRot);

			cp.X *= Map->CamZ;
			cp.Y *= Map->CamZ;

			ren_x = cp.X + (Application::WinW / 2);
			ren_y = cp.Y + (Application::WinH / 2);

			float tw, th;

			tw = tW;
			th = tH;

			float* tx = (float*)malloc(4 * 4); //new float[4];
			float* ty = (float*)malloc(4 * 4); //new float[4];

			float ax, ay;

			ax = -(lw / 2);
			ay = -(lh / 2);

			Vec2 p1, p2, p3, p4;

			p1.X = ax;
			p1.Y = ay;
			p2.X = -ax;
			p2.Y = ay;
			p3.X = -ax;
			p3.Y = -ay;
			p4.X = ax;
			p4.Y = -ay;

			p1 = rotatePoint(p1, rot);
			p2 = rotatePoint(p2, rot);
			p3 = rotatePoint(p3, rot);
			p4 = rotatePoint(p4, rot);

			p1 = vecAdd(p1, ren_x, ren_y);
			p2 = vecAdd(p2, ren_x, ren_y);
			p3 = vecAdd(p3, ren_x, ren_y);
			p4 = vecAdd(p4, ren_x, ren_y);



			tx[0] = p1.X;
			tx[1] = p2.X;
			tx[2] = p3.X;
			tx[3] = p4.X;

			ty[0] = p1.Y;
			ty[1] = p2.Y;
			ty[2] = p3.Y;
			ty[3] = p4.Y;

			Draw->DrawTexCoords(tx, ty, s->GetFrame(), s->GetFrame(), 1, 1, 1, 1);
//			UI::RenderText(tx[1], ty[1], s->GetDebugStr(), 1, 1, 1, 1, Draw);
	
			free(tx);
			free(ty);


		}

		stage3->bind();
		stage3->setInt("tR", 0);
		stage3->setInt("sW", Application::WinW);
		stage3->setInt("sH", Application::WinH);
		stage3->setInt("tS", 1);
		stage3->setInt("noLight", 0);
		stage3->setMat("proj", proj);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		for (int i = 0; i < Map->Lights.size(); i++) {

			auto l1 = Map->Lights[i];


			//l1->SetDiffuse(Vec3(1, 0, 0));



			auto pos = l1->GetPos();

			float ren_x = pos.X - Map->CamX;
			float ren_y = pos.Y - Map->CamY;

			float nx = ren_x - Application::WinW / 2;
			float ny = ren_y - Application::WinH / 2;

			Vec2 cp(nx, ny);

			cp = rotatePoint(cp, Map->CamRot);

			cp.X *= Map->CamZ;
			cp.Y *= Map->CamZ;

			ren_x = cp.X + (Application::WinW / 2);
			ren_y = cp.Y + (Application::WinH / 2);
			l1->SetRender(ren_x, ren_y, 1, l1->GetRange() * Map->CamZ);

			Vec3 nlp = l1->GetRPos();
			Vec3 ldif = l1->GetDiffuse();

			stage3->setVec3("lightPos", nlp.X, nlp.Y, 1.0f);
			stage3->setVec3("lightDiff", ldif.X, ldif.Y, ldif.Z);
			stage3->setFloat("lightRange", l1->GetRRange());

			if (l1->HasSB()) {
				l1->GetSB()->GetBB()->Bind(1);
				stage3->setInt("noShadows", 0);
			}
			else {
				stage3->setInt("noShadows", 1);

			}
			Draw->End(false);

			if (l1->HasSB()) {
				l1->GetSB()->GetBB()->Release(1);
			}
			glBlendFunc(GL_ONE, GL_ONE);
			glClear(GL_DEPTH_BUFFER_BIT);
		}

	
		stage3->unbind();

	}

	void Stage2() {

		stage2->bind();
		stage2->setInt("tR", 0);
		stage2->setInt("sW", Application::WinW);
		stage2->setInt("sH", Application::WinH);
		stage2->setInt("tS", 1);

		vMat = glm::mat4(1.0f);

		//float cz = camZ - 1.0f;

		float ox, oy;

		ox = MapW * TileW;
		ox = ox / 2;
		oy = MapH * TileH;
		oy = oy / 2;
		ox = -ox;
		oy = -oy;


		int w = Application::WinW / 2;
		int h = Application::WinH / 2;

		ox = ox + Map->CamX;
		oy = oy + Map->CamY;

		float CamX = w + ox;
		float CamY = h + oy;

		float camZ = Map->CamZ;
		float mapRot = Map->CamRot;


		float ca = TMaths::DegToRad(mapRot);


		vMat = glm::translate(vMat, glm::vec3(pw / 2, ph / 2, 0));
		vMat = glm::rotate(vMat, ca, glm::vec3(0, 0, 1));
		vMat = glm::translate(vMat, glm::vec3(-CamX, -CamY, 0));

		stage2->setMat("proj", proj);
		stage2->setMat("view", vMat);


		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);

		glBlendFunc(GL_ONE, GL_ZERO);

		//glViewport(0, 0, Application::RenW, Application::RenH);
		glClearDepth(1.0f);
		glDepthFunc(GL_LESS);
		glClear(GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < Map->Lights.size(); i++) {
		
			auto l1 = Map->Lights[i];


			//l1->SetDiffuse(Vec3(1, 0, 0));



			auto pos = l1->GetPos();

			float ren_x = pos.X - Map->CamX;
			float ren_y = pos.Y - Map->CamY;

			float nx = ren_x - Application::WinW / 2;
			float ny = ren_y - Application::WinH / 2;

			Vec2 cp(nx, ny);

			cp = rotatePoint(cp, Map->CamRot);

			cp.X *= Map->CamZ;
			cp.Y *= Map->CamZ;

			ren_x = cp.X + (Application::WinW / 2);
			ren_y = cp.Y + (Application::WinH / 2);
			l1->SetRender(ren_x, ren_y, 1, l1->GetRange() * Map->CamZ);

			Vec3 nlp = l1->GetRPos();
			Vec3 ldif = l1->GetDiffuse();

			stage2->setVec3("lightPos", nlp.X, nlp.Y, 1.0f);
			stage2->setVec3("lightDiff",ldif.X,ldif.Y,ldif.Z);
			stage2->setFloat("lightRange", l1->GetRRange());

			if (l1->HasSB()) {

				stage2->setInt("noShadows", 0);
				l1->GetSB()->GetBB()->Bind(1);
			}
			else {
				stage2->setInt("noShadows", 1);
				//l1->GetSB()->GetBB()->Bind(1);
			}
			MapMesh2->Render();

			if (l1->HasSB()) {
				l1->GetSB()->GetBB()->Release(1);
			}
			glBlendFunc(GL_ONE, GL_ONE);
			glClear(GL_DEPTH_BUFFER_BIT);
		}
		stage2->unbind();

	}
	void Stage1() {
		stage1->bind();
		stage1->setInt("tR", 0);
		stage1->setInt("sW", Application::WinW);
		stage1->setInt("sH", Application::WinH);
		stage1->setInt("tS", 1);

		vMat = glm::mat4(1.0f);

		//float cz = camZ - 1.0f;

		float ox, oy;

		ox = MapW * TileW;
		ox = ox / 2;
		oy = MapH * TileH;
		oy = oy / 2;
		ox = -ox;
		oy = -oy;


		int w = Application::WinW / 2;
		int h = Application::WinH / 2;

		ox = ox + Map->CamX;
		oy = oy + Map->CamY;

		float CamX = w + ox;
		float CamY = h + oy;

		float camZ = Map->CamZ;
		float mapRot = Map->CamRot;


		float ca = TMaths::DegToRad(mapRot);

		
		vMat = glm::translate(vMat, glm::vec3(pw / 2, ph / 2, 0));
		vMat = glm::rotate(vMat, ca, glm::vec3(0, 0, 1));
		vMat = glm::translate(vMat, glm::vec3(-CamX, -CamY, 0));
		
		stage1->setMat("proj", proj);
		stage1->setMat("view", vMat);
	

		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		
		glBlendFunc(GL_ONE, GL_ZERO);
		
	//	glViewport(0, 0, Application::RenW, Application::RenH);
		glClearDepth(1.0f);
		glDepthFunc(GL_LESS);
		
		for (int i = 0; i < Map->Lights.size(); i++) {

			auto l = Map->Lights[i];

			if (l->HasSB() == false) {
				continue;
			}

			l->GetSB()->bind();
				
			if (l->GetBakedShadows() != NULL) {

				l->GetBakedShadows()->Bind(1);
			}
			else {
				WhiteShadow->Bind(1);
			}

			MapMesh->RenderLM();
			
			if (l->GetBakedShadows() != NULL) {
				l->GetBakedShadows()->Release(1);
			}
			else {
				WhiteShadow->Release(1);
			}
			l->GetSB()->unbind();

			//break;
		}
		stage1->unbind();
	}

	void Render()
	{
		if (stage1 == NULL) {

			stage1 = new kEffect("shader/2d/mapstage1vs.glsl", "shader/2d/mapstage1fs.glsl");
			stage2 = new kEffect("shader/2d/mapstage2vs.glsl", "shader/2d/mapstage2fs.glsl");
			stage3 = new kEffect("shader/2d/mapstage3vs.glsl", "shader/2d/mapstage3fs.glsl");
		}
		pw = Application::WinW;
		ph = Application::WinH;


		proj = glm::ortho((float)0, (float)pw, (float)ph, (float)0, (float)-100, (float)100);
		Stage1();
		Stage2();
		Stage3();

		

 	//	Draw->Begin();
	//	Draw->DrawTex(0, ph, pw, -ph, l1->GetSB()->GetBB(), 1, 1, 1, 1);
	//	Draw->End();


	}

private:
	IDraw* Draw;
	Map* Map;
	int pw, ph;
	Texture2D* WhiteShadow = NULL;
	kEffect* stage1;
	kEffect* stage2;
	kEffect* stage3;
	kEffect* stage4;
	Mesh2D* MapMesh;
	Mesh2D* MapMesh2;
	int MapW, MapH;
	glm::mat4 proj;
	glm::mat4 vMat;
	int TileW, TileH;
};

