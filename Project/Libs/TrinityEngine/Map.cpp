#include "pch.h"
#include "Map.h"
#include "IDraw.h"
#include "Application.h"
#include "SimpleMath.h"
#include "ShadowBaker.h"
#include "UI.h"
#include "EngGlobal.h"

void Map::Move(float x, float y) {


	Vec2 mv(x, y);

	mv = rotatePoint(mv, -CamRot);


	CamX += mv.X / CamZ;
	CamY += mv.Y / CamZ;



}

void Map::Turn(float a) {

	CamRot += a;
	for (int i = 0; i < 8; i++) {

		if (CamRot < 0.0f)
		{
			CamRot = 360.0 + CamRot;
		}
		if (CamRot > 360.0f) CamRot = CamRot - 360.0f;

	}

}

void Map::Zoom(float a) {

	CamZ += a * 0.004f * CamZ;

}

Map::Map(int w, int h, int tw, int th,float gx,float gy) {

	MapW = w;
	MapH = h;

	rx = (float*)malloc(4 * 4);
	ry = (float*)malloc(4 * 4);

	Texture2D* img = new Texture2D("Edit/NoTile.png", false);
	LightIcon = new Texture2D("Edit/Light1.png", false);
	White = new Texture2D("Edit/shadow1.png", true);
	Circle = new Texture2D("Edit/circle.png", true);
	lightFx = new FXLight2D(Application::WinW, Application::WinH);
	shadowFx = new FXShadow2D(Application::WinW, Application::WinH);
	preShadowFx = new FXPreShadow2D(Application::WinW, Application::WinH);
	particleFx = new FXSoftParticle2D(Application::WinW, Application::WinH);
	lightMapFx = new FXLightMap2D(Application::WinW, Application::WinH);

	//while (true) {}

	//while (true) {}

	BlankNorm = new Texture2D("map/nm1.png", false);

	NoTile = img;

	Lights.resize(0);

	LeftRight = new Texture2D("ui/arrowRight.png", true);
	UpDown = new Texture2D("ui/arrowUp.png", true);
	Rotate = new Texture2D("ui/rotate.png", true);

	MapLight* l2 = new MapLight();
	MapLight* l1 = new MapLight();

	l1->SetIcon(LightIcon);
	l2->SetIcon(LightIcon);

	l2->SetPos(600, 600);
	l1->SetPos(250, 250);
	l1->SetDiffuse(Vec3(1, 1, 1));
	l2->SetDiffuse(Vec3(0, 2, 2));
	l1->SetRange(700);
	l2->SetRange(900);


//	Lights.push_back(l1);
//	Lights.push_back(l2);

	Nodes.resize(0);

//	Nodes.push_back(l1);
//	Nodes.push_back(l2);

	MapTile* baseTile = new MapTile(img);

	for (int z = 0; z < 8; z++) {
		for (int y = 0; y < MapH; y++) {

			for (int x = 0; x < MapW; x++) {

				Tiles[x][y][z] = NULL;
				Highlight[x][y] = false;
				//Tiles[x][y][0] = new MapTile(baseTile);
			}
		}
	}

	TileW = tw * 2;
		TileH = th * 2;

	CamX = 0;
	CamY = 0;

	HighLight = new Texture2D("Edit/highlight1.png", true);

	SetDraw(Application::WinW, Application::WinH);

	cpVect grav = cpv(gx,gy);

	pSpace = cpSpaceNew();
	cpSpaceSetGravity(pSpace, grav);
	Map::CurSpace = pSpace;

	dColor = new kFrameBuffer(Application::WinW, Application::WinH);
	dNormal = new kFrameBuffer(Application::WinW, Application::WinH);

	EngGlobal::CurMap = this;

	PSystems.resize(0);

};

void Map::RenderParticles() {

	Draw->Begin();



	for (int i = 0; i < PSystems.size(); i++) {

		auto ps = PSystems[i];

		ps->pmut.lock();

		//ParticleBase* pp = ps->Particles;
		int pC = 0;
		//bool ff = true;
		if (ps->pCount == 0)
		{
			ps->pmut.unlock();
			continue;

		}while (true) {

			auto ap = (ParticleBase*)ps->Particles[pC];
			
			 float tW, tH;



			tW = ap->W * CamZ;
			tH = ap->H * CamZ;

			int sW = Application::WinW;
			int sH = Application::WinH;

			int lw, lh;
			lw = 64;
			lh = 64;
			lw = lw * CamZ;
			lh = lh * CamZ;

			auto pos = Vec3(ap->X, ap->Y, ap->Z);

			float ren_x = pos.X - CamX;
			float ren_y = pos.Y - CamY;

			float nx = ren_x - DX / 2;
			float ny = ren_y - DY / 2;

			Vec2 cp(nx, ny);

			float rot = CamRot + ap->Rot;

			cp = rotatePoint(cp, CamRot);

			cp.X *= CamZ;
			cp.Y *= CamZ;

			ren_x = cp.X + (DX / 2);
			ren_y = cp.Y + (DY / 2);



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

			Draw->DrawTexCoords(tx, ty, ap->Image, BlankNorm, 1,1,1, ap->Alpha);
	
			free(tx);
			free(ty);

		
			pC++;
			if (pC >= ps->pCount) {
				break;
			}

		}
		ps->pmut.unlock();
	}

	bool first = true;

	for (int i = 0; i < Lights.size(); i++) {
		auto l1 = Lights[i];

		//l1->SetDiffuse(Vec3(1, 0, 0));

		auto pos = l1->GetPos();

		float ren_x = pos.X - CamX;
		float ren_y = pos.Y - CamY;

		float nx = ren_x - DX / 2;
		float ny = ren_y - DY / 2;

		Vec2 cp(nx, ny);

		cp = rotatePoint(cp, CamRot);

		cp.X *= CamZ;
		cp.Y *= CamZ;

		ren_x = cp.X + (DX / 2);
		ren_y = cp.Y + (DY / 2);

		l1->SetRender(ren_x, ren_y, 1, l1->GetRange() * CamZ);

		particleFx->SetLight(l1);

		kFrameBuffer* buf = l1->GetSB();

		particleFx->SetShadowMap(l1->GetSB()->GetBB());

		particleFx->SetCamZ(CamZ);
		particleFx->setMapRot(CamRot);
		Draw->End(particleFx,true,false);

		glClear(GL_DEPTH_BUFFER_BIT);

		ShadowMap->Release(2);
		first = false;
	}

}

void Map::UpdateParticles() {

	for (int i = 0; i < PSystems.size(); i++) {

		//auto ps = PSystems[i];
		//ps->Update();

	}

}


cpSpace* Map::CurSpace = NULL;

void Map::SetDraw(int w, int h) {

	Draw = new IDraw(Application::RenW, Application::RenH);
	//printf("DX:%d DY:%d\n", w, h);
	DX = w;
	DY = h;


}

void Map::SetTile(int x, int y, int z, MapTile* tile) {

	Tiles[x][y][z] = tile;

};

bool Map::PointInNode(float x, float y,int mx,int my) {

	float tW, tH;

	tW = TileW * CamZ;
	tH = TileH * CamZ;

	int lw, lh;
	lw = 64;
	lh = 64;
	lw = lw * CamZ;
	lh = lh * CamZ;

	auto pos = Vec2(x, y);

	float ren_x = pos.X - CamX;
	float ren_y = pos.Y - CamY;

	float nx = ren_x - DX / 2;
	float ny = ren_y - DY / 2;

	Vec2 cp(nx, ny);

	cp = rotatePoint(cp, CamRot);

	cp.X *= CamZ;
	cp.Y *= CamZ;

	ren_x = cp.X + (DX / 2);
	ren_y = cp.Y + (DY / 2);



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

	p1 = rotatePoint(p1, CamRot);
	p2 = rotatePoint(p2, CamRot);
	p3 = rotatePoint(p3, CamRot);
	p4 = rotatePoint(p4, CamRot);

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

	if (isInside(tx[0], ty[0], tx[1], ty[1], tx[2], ty[2], mx, my) || isInside(tx[2], ty[2], tx[3], ty[3], tx[0], ty[0], mx, my))
	{
		return true;
	}

	return false;
}

TileInfo* Map::TileAt(int mx, int my) {

	TileInfo* info = new TileInfo;
	info->Node = NULL;
	//MapTile* tile = Tiles[0][y][z];
	info->Up = false;
	info->Right = false;
	info->Rotate = false;
	info->TileX = 0;
	info->TileY = 0;
	int lw, lh;
	lw = 64;
	lh = 64;
	lw = lw * CamZ;
	lh = lh * CamZ;
	float tW, tH;

	tW = TileW * CamZ;
	tH = TileH * CamZ;

	if(ActiveNode != NULL){

		auto pos = ActiveNode->GetPos();

		if (PointInNode(pos.X + TileW / 1.3f, pos.Y + TileH / 16, mx, my)) {
			printf("Right\n");
			info->Right = true;
			return info;
		}
		else if (PointInNode(pos.X + TileW / 16.0f, pos.Y - TileH, mx, my)) {
			printf("Up\n");
			info->Up = true;
			return info;
		}
		else if (PointInNode(pos.X - TileW, pos.Y,mx,my)) {
			info->Rotate = true;
			return info;
		}


		//	RenderTexture(LeftRight, pos.X + TileW / 1.3f, pos.Y + TileH / 16);
	//	RenderTexture(UpDown, pos.X + TileW / 16.0, pos.Y - TileH);
	}



	for (int i = 0; i < Nodes.size(); i++) {

		auto l = Nodes[i];

		auto pos = l->GetPos();

		float ren_x = pos.X - CamX;
		float ren_y = pos.Y - CamY;

		float nx = ren_x - DX / 2;
		float ny = ren_y - DY / 2;

		Vec2 cp(nx, ny);

		cp = rotatePoint(cp, CamRot);

		cp.X *= CamZ;
		cp.Y *= CamZ;

		ren_x = cp.X + (DX / 2);
		ren_y = cp.Y + (DY / 2);



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

		p1 = rotatePoint(p1, CamRot);
		p2 = rotatePoint(p2, CamRot);
		p3 = rotatePoint(p3, CamRot);
		p4 = rotatePoint(p4, CamRot);

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

		if (isInside(tx[0], ty[0], tx[1], ty[1], tx[2], ty[2], mx, my) || isInside(tx[2], ty[2], tx[3], ty[3], tx[0], ty[0], mx, my))
		{
			//exit(0);
			info->Node = l;
			return info;
			//info->TileX = x;
			//info->TileY = y;
			for (int i = 0; i < 8; i++) {
//				info->Tile[i] = Tiles[x][y][i];

			}
	//		return info;
		}

		//Draw->DrawTexCoords(tx, ty, LightIcon, 1, 1, 1, 1);

		//ren_x += TileW / 2;
		///ren_y += TileH / 2;


	}
	DX = Application::RenW;
	DY = Application::RenH;

	int sW = DX;
	int sH = DY;

	//float tW, tH;

	tW = TileW * CamZ;
	tH = TileH * CamZ;


		for (int y = 0; y < MapH; y++) {

			for (int x = 0; x < MapW; x++) {


				MapTile* tile = Tiles[x][y][0];
				float ren_x = (x * TileW) - CamX;
				float ren_y = (y * TileH) - CamY;




				ren_x += TileW / 2;
				ren_y += TileH / 2;

				float nx = ren_x - DX / 2;
				float ny = ren_y - DY / 2;

				Vec2 cp(nx, ny);

				cp = rotatePoint(cp, CamRot);

				cp.X *= CamZ;
				cp.Y *= CamZ;

				ren_x = cp.X + (DX / 2);
				ren_y = cp.Y + (DY / 2);



				float tw, th;

				tw = tW;
				th = tH;
				float* tx, * ty;
				tx = rx;
				ty = ry;
				/*if (TileX[x][y] == NULL) {
					//tx = (float*)malloc(4 * 4); //new float[4];
					//ty = (float*)malloc(4 * 4); //new float[4];
					//TileX[x][y] = tx;
					//TileY[x][y] = ty;
				}
				else {
					//tx = TileX[x][y];
					//ty = TileY[x][y];
				}
				*/
				float ax, ay;

				ax = -(tw / 2);
				ay = -(th / 2);

				Vec2 p1, p2, p3, p4;

				p1.X = ax;
				p1.Y = ay;
				p2.X = -ax;
				p2.Y = ay;
				p3.X = -ax;
				p3.Y = -ay;
				p4.X = ax;
				p4.Y = -ay;

				p1 = rotatePoint(p1, CamRot);
				p2 = rotatePoint(p2, CamRot);
				p3 = rotatePoint(p3, CamRot);
				p4 = rotatePoint(p4, CamRot);

				p1 = vecAdd(p1, ren_x, ren_y);
				p2 = vecAdd(p2, ren_x, ren_y);
				p3 = vecAdd(p3, ren_x, ren_y);
				p4 = vecAdd(p4, ren_x, ren_y);

				int stw = TileW * CamZ;
				int sth = TileH * CamZ;

				stw = stw * 2;
				sth = sth * 2;

				if (p1.X < (-stw) || p1.X>(sW + stw) || p3.X<(-sth) || p3.X>(sW + sth))
				{
					continue;
				}
				if (p1.Y <(-stw) || p1.Y >(sH + sth) || p3.Y <-stw || p3.Y>(sH + sth))
				{

					continue;
				}

				tx[0] = p1.X;
				tx[1] = p2.X;
				tx[2] = p3.X;
				tx[3] = p4.X;

				ty[0] = p1.Y;
				ty[1] = p2.Y;
				ty[2] = p3.Y;
				ty[3] = p4.Y;

				if (tx == NULL) continue;

				if (isInside(tx[0], ty[0], tx[1], ty[1], tx[2], ty[2], mx, my) || isInside(tx[2],ty[2],tx[3],ty[3],tx[0],ty[0],mx,my))
				{
					info->TileX = x;
					info->TileY = y;
					for (int i = 0;i < 8;i++) {
						info->Tile[i] = Tiles[x][y][i];

					}
					return info;
				}

				/*
				int ren_x = (x * TileW) - CamX;
				int ren_y = (y * TileH) - CamY;

				if (mx >= ren_x && mx <= (ren_x + TileW)) {
					if (my >= ren_y && my <= (ren_y + TileH)) {

						info->TileX = x;
						info->TileY = y;
						for (int i = 0; i < 8; i++) {
							info->Tile[i] = Tiles[x][y][i];
						}
						//printf("TXX:%d TYY:%d W:%d H:%d\n", x, y, TileW, TileH);
						//printf("RX:%d RY:%d\n", ren_x, ren_y);
						return info;

					}
				}
				*/


			}

		}


	info->TileX = -1;
	return info;

};

void Map::Compile() {

	CompiledMesh = new Mesh2D();
	ShadowMesh = new Mesh2D();
	CompiledMeshStatic = new Mesh2D();

	//int ox, oy;

	float ox = (MapW*TileW) / 2;
	float oy = (MapH*TileH) / 2;

	ox = -ox;
	oy = -oy;

	float mapW = GetW();
	float mapH = GetH();

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


				MapTile* tile = Tiles[x][y][z];

				if (tile != NULL) {

					if (tile->GetCastsShadow()) {

						ShadowMesh->AddQuad(tx, ty, TileW, TileH, tile->GetImage(), tile->GetNormal(), 1, 1, 1, 1);

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


					CompiledMesh->AddQuad(tx, ty, TileW, TileH, tile->GetImage(), tile->GetNormal(),1,1,1,1);
					CompiledMeshStatic->AddQuadLM(tx, ty, TileW, TileH,u1,v1,u2,v2, tile->GetImage(), tile->GetNormal(), 1, 1, 1, 1);


				}


			}
		}
	}

	CompiledMesh->Compile();
	ShadowMesh->Compile();
	CompiledMeshStatic->CompileLM();

}

void Map::RenderCompiled() {


	bool first = true;




	for (int i = 0; i < Lights.size(); i++) {
		auto l1 = Lights[i];

		//l1->SetDiffuse(Vec3(1, 0, 0));

	

		auto pos = l1->GetPos();

		float ren_x = pos.X - CamX;
		float ren_y = pos.Y - CamY;

		float nx = ren_x - DX / 2;
		float ny = ren_y - DY / 2;

		Vec2 cp(nx, ny);

		cp = rotatePoint(cp, CamRot);

		cp.X *= CamZ;
		cp.Y *= CamZ;

		ren_x = cp.X + (DX / 2);
		ren_y = cp.Y + (DY / 2);

		
	//	if (z == z) {

		if (l1->GetDynamic()) {

			l1->SetRender(ren_x, ren_y, 1, l1->GetRange() * CamZ);

			lightFx->SetLight(l1);

			kFrameBuffer* buf = l1->GetSB();

			buf->GetBB()->Bind(2);

			lightFx->SetShadowMap(l1->GetSB()->GetBB());

			lightFx->SetCamZ(CamZ);
			lightFx->setMapRot(CamRot);

			float ox, oy;

			ox = MapW * TileW;
			ox = ox / 2;
			oy = MapH * TileH;
			oy = oy / 2;
			ox = -ox;
			oy = -oy;


			int w = Application::WinW / 2;
			int h = Application::WinH / 2;

			ox = ox + CamX;
			oy = oy + CamY;

			lightFx->SetCam(w + ox, h + oy, CamZ, CamRot);

			CompiledMesh->Render(lightFx, first);
			glClear(GL_DEPTH_BUFFER_BIT);


			glClear(GL_DEPTH_BUFFER_BIT);

			buf->GetBB()->Release(2);
			//ShadowMap->Release(2);
		}
		else {
			l1->SetRender(ren_x, ren_y, 1, l1->GetRange() * CamZ);
			//lightFx->SetShadowMap(l1->GetSB()->GetBB());
			lightMapFx->SetLight(l1);

			lightMapFx->SetCamZ(CamZ);
			lightMapFx->setMapRot(CamRot);

			float ox, oy;

			ox = MapW * TileW;
			ox = ox / 2;
			oy = MapH * TileH;
			oy = oy / 2;
			ox = -ox;
			oy = -oy;


			int w = Application::WinW / 2;
			int h = Application::WinH / 2;

			ox = ox + CamX;
			oy = oy + CamY;

			lightMapFx->SetCam(w + ox, h + oy, CamZ, CamRot);

			CompiledMeshStatic->RenderLM(lightMapFx, first);
			glClear(GL_DEPTH_BUFFER_BIT);

			l1->GetBakedShadows()->Release(2);


		}

		first = false;
		
	}


	first = true;


	Draw->Begin();


	int lw, lh;
	lw = 64;
	lh = 64;
	lw = lw * CamZ;
	lh = lh * CamZ;

	//RenderTexture(LightIcon, 300, 320);

	for (int i = 0; i < Nodes.size(); i++) {

		auto l = Nodes[i];

		auto pos = l->GetPos();

		//RenderNode(l);

		//ren_x += TileW / 2;
		///ren_y += TileH / 2;


	}

	for (int i = 0; i < Decals.size(); i++) {

		auto d = Decals[i];

		RenderDecal(d);

	}

	for (int i = 0; i < Sprites.size(); i++) {

		auto s = Sprites[i];

		RenderSprite(s);

	}
	for (int i = 0; i < Lights.size(); i++) {
		auto l1 = Lights[i];

		//l1->SetDiffuse(Vec3(1, 0, 0));

		auto pos = l1->GetPos();

		float ren_x = pos.X - CamX;
		float ren_y = pos.Y - CamY;

		float nx = ren_x - DX / 2;
		float ny = ren_y - DY / 2;

		Vec2 cp(nx, ny);

		cp = rotatePoint(cp, CamRot);

		cp.X *= CamZ;
		cp.Y *= CamZ;

		ren_x = cp.X + (DX / 2);
		ren_y = cp.Y + (DY / 2);

		//float dis = 


		l1->SetRender(ren_x, ren_y, 1, l1->GetRange() * CamZ);

		lightFx->SetLight(l1);
		lightFx->SetShadowMap(l1->GetSB()->GetBB());
		lightFx->SetCamZ(CamZ);

		lightFx->useVmat(false);

		Draw->End(lightFx, first);

		lightFx->useVmat(true);

		glClear(GL_DEPTH_BUFFER_BIT);

		ShadowMap->Release(2);
		first = false;
	}


	RenderParticles();


}

void rcFunc(cpShape* s,cpVect point, cpVect n,cpFloat alpha, void* data) {

	HitInfo* hi = (HitInfo*)data;
	
	float xd = point.x - hi->sx;
	float yd = point.y - hi->sy;

	float dis = sqrt(xd * xd + yd * yd);
	if (dis < hi->dis) {

		hi->dis = dis;
		hi->HitX = point.x;
		hi->HitY = point.y;
		hi->NX = n.x;
		hi->NY = n.y;
		hi->Hit = true;
		hi->shape = s;

	}


}


HitInfo Map::Raycast(float x, float y, float x1, float y1)
{

	cpVect a = cpv(x, y);
	cpVect b = cpv(x1, y1);
	cpShapeFilter f;
	f.categories = 1;
	f.mask = 1;
	f.group = 1;

	HitInfo ri;
	ri.Hit = false;
	ri.HitX = 0;
	ri.HitY = 0;
	ri.dis = 90000;
	ri.sx = x;
	ri.sy = y;
	ri.spr = NULL;
	
	cpSpaceSegmentQueryFunc fu;

	fu = rcFunc;


	cpSpaceSegmentQuery(pSpace, b, a, 1, CP_SHAPE_FILTER_ALL,fu, &ri);

	if (ri.Hit) {

		
		ri.spr = GetSpriteWithShape(ri.shape);

	}

	return ri;

	if (ri.Hit) {
	
	
		//	exit(1);
	}

	/*
	cpSegmentQueryInfo info = {};
	if (cpSpaceSegmentQueryFirst(pSpace, a, b, -1, CP_SHAPE_FILTER_ALL, &info) != NULL) {
		cpSegmentQueryInfo info2;
		cpShapeSegmentQuery(info.shape, b, a, 0, &info2);



		HitInfo in;
		in.HitX = info2.point.x;
		in.HitY = info2.point.y;
		in.Hit = true;

		return in;

		//cpVect enterPoint = cpSegmentQueryHitPoint(a, b, info);

		//cpVect exitPoint = cpSegmentQueryHitPoint(b, a, info2);
	}
	*/

	//HitInfo in;
	return ri;

}


//float rotX(float x, float ang, float s = 1.0f)
//{

void Draw(float x, float y, float rot, float z) {



}

void Map::Fill(MapTile* t, int z) {

	for (int y = 0; y < MapH; y++) {

		for (int x = 0; x < MapW; x++) {

			Tiles[x][y][z] = t;

		}

	}

}

void Map::RenderShadows2(Texture2D* bb) {

	int w = Application::WinW;
	int h = Application::WinH;

	DX = w;
	DY = h;

	Draw->Begin();

	Draw->DrawTex(0, h, w, -h, bb, 1, 1, 1, 1);

	for (int i = 0; i < Lights.size(); i++) {

		auto l1 = Lights[i];

		auto pos = l1->GetPos();

		float ren_x = pos.X - CamX;
		float ren_y = pos.Y - CamY;

		float nx = ren_x - DX / 2;
		float ny = ren_y - DY / 2;

		Vec2 cp(nx, ny);

		cp = rotatePoint(cp, CamRot);

		cp.X *= CamZ;
		cp.Y *= CamZ;

		ren_x = cp.X + (DX / 2);
		ren_y = cp.Y + (DY / 2);

		l1->SetRender(ren_x, ren_y, 1, l1->GetRange() * CamZ);

		lightFx->SetLight(l1);
	
		lightFx->SetCamZ(CamZ);
		lightFx->setMapRot(CamRot);

		l1->BindSB();
		shadowFx->SetLight(l1);
		
		Draw->End(shadowFx, true);

		//return;

		l1->UnbindSB();
	}


}

void Map::RenderShadows1() {

	//RenderCompiled();

	//preShadowFx->bind();

	//preShadowFx->setMapRot(CamRot);

	float ox, oy;

	ox = MapW * TileW;
	ox = ox / 2;
	oy = MapH * TileH;
	oy = oy / 2;
	ox = -ox;
	oy = -oy;


	int w = Application::WinW / 2;
	int h = Application::WinH / 2;

	ox = ox + CamX;
	oy = oy + CamY;

	preShadowFx->SetCam(w + ox, h + oy, CamZ, CamRot);

	ShadowMesh->Render(preShadowFx,true);


	preShadowFx->unbind();

	return;
	//
	Draw->Begin();
	//CamZ = 2.5f;

//	CamZ = CamZ + 0.01f;
	DX = Application::RenW;
	DY = Application::RenH;

	int sW = DX;
	int sH = DY;

	float tW, tH;

	tW = TileW * CamZ;
	tH = TileH * CamZ;


	for (int z = 0; z < 4; z++) {
		for (int y = 0; y < MapH; y++) {
			for (int x = 0; x < MapW; x++) {

				float ren_x = (x * TileW) - CamX;
				float ren_y = (y * TileH) - CamY;




				ren_x += TileW / 2;
				ren_y += TileH / 2;

				float nx = ren_x - DX / 2;
				float ny = ren_y - DY / 2;

				Vec2 cp(nx, ny);

				cp = rotatePoint(cp, CamRot);

				cp.X *= CamZ;
				cp.Y *= CamZ;

				ren_x = cp.X + (DX / 2);
				ren_y = cp.Y + (DY / 2);



				float tw, th;

				tw = tW;
				th = tH;

				float* tx;// = (float*)malloc(4 * 4); //new float[4];
				float* ty;// = (float*)malloc(4 * 4); //new float[4];
				tx = rx;
				ty = ry;
				float ax, ay;

				ax = -(tw / 2);
				ay = -(th / 2);

				Vec2 p1, p2, p3, p4;

				p1.X = ax;
				p1.Y = ay;
				p2.X = -ax;
				p2.Y = ay;
				p3.X = -ax;
				p3.Y = -ay;
				p4.X = ax;
				p4.Y = -ay;

				p1 = rotatePoint(p1, CamRot);
				p2 = rotatePoint(p2, CamRot);
				p3 = rotatePoint(p3, CamRot);
				p4 = rotatePoint(p4, CamRot);

				p1 = vecAdd(p1, ren_x, ren_y);
				p2 = vecAdd(p2, ren_x, ren_y);
				p3 = vecAdd(p3, ren_x, ren_y);
				p4 = vecAdd(p4, ren_x, ren_y);

				int stw = TileW;
				int sth = TileH;

				stw = stw * 3;
				sth = sth * 3;

				if (p1.X < (-stw) || p1.X>(sW + stw) || p3.X<(-sth) || p3.X>(sW + sth))
				{
				
					continue;
				}
				if (p1.Y <(-stw) || p1.Y >(sH + sth) || p3.Y <-stw || p3.Y>(sH + sth))
				{
				
					continue;
				}

				tx[0] = p1.X;
				tx[1] = p2.X;
				tx[2] = p3.X;
				tx[3] = p4.X;

				ty[0] = p1.Y;
				ty[1] = p2.Y;
				ty[2] = p3.Y;
				ty[3] = p4.Y;


				MapTile* tile = Tiles[x][y][z];
			
				//T/ileX[x][y] = tx;
				//TileY[x][y] = ty;

				if (tile != NULL) {

					if (!tile->GetCastsShadow()) {
						tile = NULL;
					}

				}

				if (tile != NULL) {

					Texture2D* img = NULL;
				
					img = tile->GetImage();
			
					Draw->DrawTexCoords(tx, ty, img, 1, 1, 1, 1);
					//Draw->DrawTex(ren_x, ren_y, TileW, TileH, img, 1, 1, 1, 1);
					//printf("MapX:%d MapY:%d\n", ren_x, ren_y);
					//
				}
				else {

					if (z == 0) {
						Draw->DrawTexCoords(tx, ty, White, 1, 1, 1, 1);
					}
				}

		
				

			}
		}
		int lw, lh;
		lw = 64;
		lh = 64;
		lw = lw * CamZ;
		lh = lh * CamZ;

		//RenderTexture(LightIcon, 300, 320);

		for (int i = 0; i < Sprites.size(); i++) {

		//	RenderSprite(Sprites[i]);

		}

		for (int i = 0; i < Nodes.size(); i++) {

			auto l = Nodes[i];

			auto pos = l->GetPos();

			//RenderNodeShadow(l);

			//ren_x += TileW / 2;
			///ren_y += TileH / 2;


		}
	}
	Draw->End(preShadowFx,true);
}

void Map::RenderTexture(Texture2D* img, float x, float y,float siz,float cr,float cg,float cb)
{

	float tW, tH;

	tW = TileW * CamZ;
	tH = TileH * CamZ;

	int lw, lh;
	if (siz == -1) {
		lw = 64;
		lh = 64;
	}
	else {
		lw = siz;
		lh = siz;
	}
	lw = lw * CamZ;
	lh = lh * CamZ;

	auto pos = Vec2(x, y);

	float ren_x = pos.X - CamX;
	float ren_y = pos.Y - CamY;

	float nx = ren_x - DX / 2;
	float ny = ren_y - DY / 2;

	Vec2 cp(nx, ny);

	cp = rotatePoint(cp, CamRot);

	cp.X *= CamZ;
	cp.Y *= CamZ;

	ren_x = cp.X + (DX / 2);
	ren_y = cp.Y + (DY / 2);



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

	p1 = rotatePoint(p1, CamRot);
	p2 = rotatePoint(p2, CamRot);
	p3 = rotatePoint(p3, CamRot);
	p4 = rotatePoint(p4, CamRot);

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

	Draw->DrawTexCoords(tx, ty, img, BlankNorm, cr,cg, cb, 1);
	
}

void Map::RenderNodeShadow(MapNode* l) {
	float tW, tH;
	if (l->GetType() == NodeType::TypeLight) return;
	tW = TileW * CamZ;
	tH = TileH * CamZ;

	int lw, lh;
	lw = 64;
	lh = 64;
	lw = lw * CamZ;
	lh = lh * CamZ;

	auto pos = l->GetPos();

	float ren_x = pos.X - CamX;
	float ren_y = pos.Y - CamY;

	float nx = ren_x - DX / 2;
	float ny = ren_y - DY / 2;

	Vec2 cp(nx, ny);

	float rot = CamRot + l->GetRot();

	cp = rotatePoint(cp, CamRot);

	cp.X *= CamZ;
	cp.Y *= CamZ;

	ren_x = cp.X + (DX / 2);
	ren_y = cp.Y + (DY / 2);



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

	Draw->DrawTexCoords(tx, ty, l->GetShadow(), BlankNorm, 1, 1, 1, 1);
	if (l == ActiveNode)
	{
	//	Draw->DrawTexCoords(tx, ty, HighLight, BlankNorm, 1, 1, 1, 1);
		//..exit(1);


	}

}

void Map::RenderDecal(MapDecal* d)
{


	float tW, tH;

	tW = TileW * CamZ;
	tH = TileH * CamZ;

	int sW = Application::WinW;
	int sH = Application::WinH;

	int lw, lh;
	lw = d->GetWidth();
	lh = d->GetHeight();
	lw = lw * CamZ;
	lh = lh * CamZ;

	auto pos = d->GetPos();

	float ren_x = pos.X - CamX;
	float ren_y = pos.Y - CamY;

	float nx = ren_x - DX / 2;
	float ny = ren_y - DY / 2;

	Vec2 cp(nx, ny);

	float rot = CamRot + d->GetRot();

	rot = rot + 90.0f + 180.0f;

	cp = rotatePoint(cp, CamRot);

	cp.X *= CamZ;
	cp.Y *= CamZ;

	ren_x = cp.X + (DX / 2);
	ren_y = cp.Y + (DY / 2);



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

	Draw->DrawTexCoords(tx, ty,d->GetDecalTex(), BlankNorm, 1, 1, 1, 1);
	//UI::RenderText(tx[1], ty[1], s->GetDebugStr(), 1, 1, 1, 1, Draw);
	free(tx);

	free(ty);

}

void Map::RenderSprite(MapSprite* s) {

	float tW, tH;

	tW = TileW * CamZ;
	tH = TileH * CamZ;

	int sW = Application::WinW;
	int sH = Application::WinH;

	int lw, lh;
	lw = s->GetWidth();
	lh = s->GetHeight();
	lw = lw * CamZ;
	lh = lh * CamZ;

	auto pos = s->GetPos();

	float ren_x = pos.X - CamX;
	float ren_y = pos.Y - CamY;

	float nx = ren_x - DX / 2;
	float ny = ren_y - DY / 2;

	Vec2 cp(nx, ny);

	float rot = CamRot + s->GetRot();

	rot = rot + 90.0f+180.0f;

	cp = rotatePoint(cp, CamRot);

	cp.X *= CamZ;
	cp.Y *= CamZ;

	ren_x = cp.X + (DX / 2);
	ren_y = cp.Y + (DY / 2);



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

	Draw->DrawTexCoords(tx, ty, s->GetFrame(), BlankNorm, 1, 1, 1, 1);
	UI::RenderText(tx[1], ty[1], s->GetDebugStr(), 1, 1, 1, 1, Draw);
	free(tx);
	free(ty);
	
}

void Map::RenderNode(MapNode* l,float r,float g,float b) {

	float tW, tH;

	tW = l->GetW() * CamZ;
	tH = l->GetH() * CamZ;

	int sW = Application::WinW;
	int sH = Application::WinH;

	int lw, lh;
	lw = l->GetW();
	lh = l->GetH();
	lw = lw * CamZ;
	lh = lh * CamZ;

	auto pos = l->GetPos();

	float ren_x = pos.X - CamX;
	float ren_y = pos.Y - CamY;

	float nx = ren_x - DX / 2;
	float ny = ren_y - DY / 2;

	Vec2 cp(nx, ny);

	float rot = CamRot + l->GetRot();

	cp = rotatePoint(cp,CamRot);

	cp.X *= CamZ;
	cp.Y *= CamZ;

	ren_x = cp.X + (DX / 2);
	ren_y = cp.Y + (DY / 2);



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

	Draw->DrawTexCoords(tx, ty, l->GetImage(), BlankNorm, r,g,b, 1);
	if (l == ActiveNode)
	{
		Draw->DrawTexCoords(tx, ty, HighLight, BlankNorm, 1, 1, 1, 1);
		//..exit(1);


	}

}

void Map::RenderDeferred() {

	dColor->bind();

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	DX = Application::RenW;
	DY = Application::RenH;

	int sW = DX;
	int sH = DY;

	float tW, tH;

	tW = TileW * CamZ;
	tH = TileH * CamZ;

	Draw->Begin();




	for (int z = 0; z < 7; z++) {
		for (int y = 0; y < MapH; y++) {
			for (int x = 0; x < MapW; x++) {

				float ren_x = (x * TileW) - CamX;
				float ren_y = (y * TileH) - CamY;




				ren_x += TileW / 2;
				ren_y += TileH / 2;

				float nx = ren_x - DX / 2;
				float ny = ren_y - DY / 2;

				Vec2 cp(nx, ny);

				cp = rotatePoint(cp, CamRot);

				cp.X *= CamZ;
				cp.Y *= CamZ;

				ren_x = cp.X + (DX / 2);
				ren_y = cp.Y + (DY / 2);



				float tw, th;

				tw = tW;
				th = tH;

				float* tx = (float*)malloc(4 * 4); //new float[4];
				float* ty = (float*)malloc(4 * 4); //new float[4];

				float ax, ay;

				ax = -(tw / 2);
				ay = -(th / 2);

				Vec2 p1, p2, p3, p4;

				p1.X = ax;
				p1.Y = ay;
				p2.X = -ax;
				p2.Y = ay;
				p3.X = -ax;
				p3.Y = -ay;
				p4.X = ax;
				p4.Y = -ay;

				p1 = rotatePoint(p1, CamRot);
				p2 = rotatePoint(p2, CamRot);
				p3 = rotatePoint(p3, CamRot);
				p4 = rotatePoint(p4, CamRot);

				p1 = vecAdd(p1, ren_x, ren_y);
				p2 = vecAdd(p2, ren_x, ren_y);
				p3 = vecAdd(p3, ren_x, ren_y);
				p4 = vecAdd(p4, ren_x, ren_y);

				int stw = TileW * CamZ;
				int sth = TileH * CamZ;

				stw = stw * 3;
				sth = sth * 3;

				if (p1.X < (-stw) || p1.X>(sW + stw) || p3.X<(-sth) || p3.X>(sW + sth))
				{
					continue;
				}
				if (p1.Y <(-stw) || p1.Y >(sH + sth) || p3.Y <-stw || p3.Y>(sH + sth))
				{

					continue;
				}

				tx[0] = p1.X;
				tx[1] = p2.X;
				tx[2] = p3.X;
				tx[3] = p4.X;

				ty[0] = p1.Y;
				ty[1] = p2.Y;
				ty[2] = p3.Y;
				ty[3] = p4.Y;


				MapTile* tile = Tiles[x][y][z];
				TileX[x][y] = tx;
				TileY[x][y] = ty;

				if (tile != NULL) {
					if (z == 0) {
						//	tile->SetT(tx, ty);
					}
					Texture2D* img = tile->GetImage();


					Draw->DrawTexCoords(tx, ty, img, tile->GetNormal(), 1, 1, 1, 1);
					//Draw->DrawTex(ren_x, ren_y, TileW, TileH, img, 1, 1, 1, 1);
					//printf("MapX:%d MapY:%d\n", ren_x, ren_y);
					//
				}


			}
		}
	}

	//Draw->Begin();


	int lw, lh;
	lw = 64;
	lh = 64;
	lw = lw * CamZ;
	lh = lh * CamZ;

	//RenderTexture(LightIcon, 300, 320);
	

	for (int i = 0; i < Sprites.size(); i++) {

		auto s = Sprites[i];

		RenderSprite(s);

	}

	


	Draw->End();

	dColor->unbind();
	//bool first = true;

	dNormal->bind();

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


	for (int z = 0; z < 7; z++) {
		for (int y = 0; y < MapH; y++) {
			for (int x = 0; x < MapW; x++) {

				float ren_x = (x * TileW) - CamX;
				float ren_y = (y * TileH) - CamY;




				ren_x += TileW / 2;
				ren_y += TileH / 2;

				float nx = ren_x - DX / 2;
				float ny = ren_y - DY / 2;

				Vec2 cp(nx, ny);

				cp = rotatePoint(cp, CamRot);

				cp.X *= CamZ;
				cp.Y *= CamZ;

				ren_x = cp.X + (DX / 2);
				ren_y = cp.Y + (DY / 2);



				float tw, th;

				tw = tW;
				th = tH;

				float* tx = (float*)malloc(4 * 4); //new float[4];
				float* ty = (float*)malloc(4 * 4); //new float[4];

				float ax, ay;

				ax = -(tw / 2);
				ay = -(th / 2);

				Vec2 p1, p2, p3, p4;

				p1.X = ax;
				p1.Y = ay;
				p2.X = -ax;
				p2.Y = ay;
				p3.X = -ax;
				p3.Y = -ay;
				p4.X = ax;
				p4.Y = -ay;

				p1 = rotatePoint(p1, CamRot);
				p2 = rotatePoint(p2, CamRot);
				p3 = rotatePoint(p3, CamRot);
				p4 = rotatePoint(p4, CamRot);

				p1 = vecAdd(p1, ren_x, ren_y);
				p2 = vecAdd(p2, ren_x, ren_y);
				p3 = vecAdd(p3, ren_x, ren_y);
				p4 = vecAdd(p4, ren_x, ren_y);

				int stw = TileW * CamZ;
				int sth = TileH * CamZ;

				stw = stw * 3;
				sth = sth * 3;

				if (p1.X < (-stw) || p1.X>(sW + stw) || p3.X<(-sth) || p3.X>(sW + sth))
				{
					continue;
				}
				if (p1.Y <(-stw) || p1.Y >(sH + sth) || p3.Y <-stw || p3.Y>(sH + sth))
				{

					continue;
				}

				tx[0] = p1.X;
				tx[1] = p2.X;
				tx[2] = p3.X;
				tx[3] = p4.X;

				ty[0] = p1.Y;
				ty[1] = p2.Y;
				ty[2] = p3.Y;
				ty[3] = p4.Y;


				MapTile* tile = Tiles[x][y][z];
				TileX[x][y] = tx;
				TileY[x][y] = ty;

				if (tile != NULL) {
					if (z == 0) {
						//	tile->SetT(tx, ty);
					}
					Texture2D* img = tile->GetImage();


					Draw->DrawTexCoords(tx, ty,tile->GetNormal(),NULL, 1, 1, 1, 1);
					//Draw->DrawTex(ren_x, ren_y, TileW, TileH, img, 1, 1, 1, 1);
					//printf("MapX:%d MapY:%d\n", ren_x, ren_y);
					//
				}


			}
		}
	}

	


	Draw->End();

	dNormal->unbind();

	Draw->Begin();

	float* tx = (float*)malloc(4 * 4);
	float* ty = (float*)malloc(4 * 4);


	tx[0] = 0;
	tx[1] = DX;
	tx[2] = DX;
	tx[3] = 0;

	ty[0] = DY;
	ty[1] = DY;
	ty[2] = 0;
	ty[3] = 0;

	Draw->DrawTexCoords(tx,ty,dColor->GetBB(),dNormal->GetBB(), 1, 1, 1, 1);


	bool first = true;
	for (int i = 0; i < Lights.size(); i++) {
		auto l1 = Lights[i];

		//l1->SetDiffuse(Vec3(1, 0, 0));

		auto pos = l1->GetPos();

		float ren_x = pos.X - CamX;
		float ren_y = pos.Y - CamY;

		float nx = ren_x - DX / 2;
		float ny = ren_y - DY / 2;

		Vec2 cp(nx, ny);

		cp = rotatePoint(cp, CamRot);

		cp.X *= CamZ;
		cp.Y *= CamZ;

		ren_x = cp.X + (DX / 2);
		ren_y = cp.Y + (DY / 2);

		l1->SetRender(ren_x, ren_y, 1, l1->GetRange() * CamZ);

		lightFx->SetLight(l1);
		//if (z == 0) {
			lightFx->SetShadowMap(ShadowMap);
		
		lightFx->SetCamZ(CamZ);
		lightFx->setMapRot(CamRot);
		Draw->End(lightFx, first);

		glClear(GL_DEPTH_BUFFER_BIT);

		ShadowMap->Release(2);
		first = false;
	}


//dColor->unbind();

};

void Map::Render() {


//	CamRot = CamRot + 0.1f;
	
	//CamZ = 2.5f;

//	CamZ = CamZ + 0.01f;
	DX = Application::RenW;
	DY = Application::RenH;

	int sW = DX;
	int sH = DY;

	float tW, tH;

	tW = TileW * CamZ;
	tH = TileH * CamZ;
	
	glClear(GL_DEPTH_BUFFER_BIT);

	Draw->Begin();
	for (int z = 0; z < 8; z++) {



		for (int y = 0; y < MapH; y++) {
			for (int x = 0; x < MapW; x++) {

				float ren_x = (x * TileW) - CamX;
				float ren_y = (y * TileH) - CamY;




				ren_x += TileW / 2;
				ren_y += TileH / 2;

				float nx = ren_x - DX / 2;
				float ny = ren_y - DY / 2;

				Vec2 cp(nx, ny);

				cp = rotatePoint(cp, CamRot);

				cp.X *= CamZ;
				cp.Y *= CamZ;

				ren_x = cp.X + (DX / 2);
				ren_y = cp.Y + (DY / 2);



				float tw, th;

				tw = tW;
				th = tH;
				float* tx, * ty;
				tx = rx;
				ty = ry;
				/*if (TileX[x][y] == NULL) {
					//tx = (float*)malloc(4 * 4); //new float[4];
					//ty = (float*)malloc(4 * 4); //new float[4];
					//TileX[x][y] = tx;
					//TileY[x][y] = ty;
				}
				else {
					//tx = TileX[x][y];
					//ty = TileY[x][y];
				}
				*/
				float ax, ay;

				ax = -(tw / 2);
				ay = -(th / 2);

				Vec2 p1, p2, p3, p4;

				p1.X = ax;
				p1.Y = ay;
				p2.X = -ax;
				p2.Y = ay;
				p3.X = -ax;
				p3.Y = -ay;
				p4.X = ax;
				p4.Y = -ay;

				p1 = rotatePoint(p1, CamRot);
				p2 = rotatePoint(p2, CamRot);
				p3 = rotatePoint(p3, CamRot);
				p4 = rotatePoint(p4, CamRot);

				p1 = vecAdd(p1, ren_x, ren_y);
				p2 = vecAdd(p2, ren_x, ren_y);
				p3 = vecAdd(p3, ren_x, ren_y);
				p4 = vecAdd(p4, ren_x, ren_y);

				int stw = TileW * CamZ;
				int sth = TileH * CamZ;

				stw = stw * 2;
				sth = sth * 2;

				if (p1.X < (-stw) || p1.X>(sW + stw) || p3.X<(-sth) || p3.X>(sW + sth))
				{
					continue;
				}
				if (p1.Y <(-stw) || p1.Y >(sH + sth) || p3.Y <-stw || p3.Y>(sH + sth))
				{

					continue;
				}

				tx[0] = p1.X;
				tx[1] = p2.X;
				tx[2] = p3.X;
				tx[3] = p4.X;

				ty[0] = p1.Y;
				ty[1] = p2.Y;
				ty[2] = p3.Y;
				ty[3] = p4.Y;


				MapTile* tile = Tiles[x][y][z];

				if (TileX[x][y] == NULL) {

					//TileX[x][y] = (float*)malloc(4 * 4);
					//ileY[x][y] = (float*)malloc(4 * 4);


				}

				TileX[x][y] = tx;
				TileY[x][y] = ty;



				if (tile != NULL) {

					Texture2D* img = tile->GetImage();


					Draw->DrawTexCoords(tx, ty, img, tile->GetNormal(), 1, 1, 1, 1);
					//Draw->DrawTex(ren_x, ren_y, TileW, TileH, img, 1, 1, 1, 1);
					//printf("MapX:%d MapY:%d\n", ren_x, ren_y);
					//
				}
				else {

					if (z == 0) {

						Texture2D* img1 = NoTile;

						Draw->DrawTexCoords(tx, ty, img1, BlankNorm, 1, 1, 1, 1);

					}

				}
				if (z == 7) {


					if (Highlight[x][y])
					{
						Draw->DrawTexCoords(tx, ty, HighLight, BlankNorm, 1, 1, 1, 1);
						//printf("Drawing highlight:X:%d Y:%d \n", x, y);
						//Draw->DrawTex(ren_x, ren_y, TileW, TileH, HighLight, 1, 1, 1, 1);
					}


				}

			}
		}
	}


		

		bool first = true;



	//	Draw->End();

	

	int lw, lh;
	lw = 64;
	lh = 64;
	lw = lw * CamZ;
	lh = lh * CamZ;

	//RenderTexture(LightIcon, 300, 320);

	for (int i = 0; i < Nodes.size(); i++) {

		auto l = Nodes[i];

		auto pos = l->GetPos();

		if (l->GetType() == NodeType::TypeLight)
		{
			auto tl = (MapLight*)l;

			auto dif = tl->GetDiffuse();

			RenderNode(l, dif.X, dif.Y, dif.Z);
		}
		else {
			RenderNode(l);
		}
		if (l == ActiveNode) {

			RenderTexture(LeftRight, pos.X+TileW/1.3f , pos.Y + TileH/16);
			RenderTexture(UpDown, pos.X + TileW / 16.0, pos.Y - TileH);
			RenderTexture(Rotate, pos.X-TileW, pos.Y);
		}
		//ren_x += TileW / 2;
		///ren_y += TileH / 2;


	}
	for (int i = 0; i < Lights.size(); i++) {

		auto l = Lights[i];

		auto pos = l->GetPos();
		auto r = l->GetRange();
		auto col = l->GetDiffuse();


		if (ActiveNode == l) {
			RenderTexture(Circle, pos.X, pos.Y, r * 2, col.X, col.Y, col.Z);
		}
		//DrawCircle(pos.X, pos.Y, r);


	}
	/*
	for (int y = 0; y < MapH; y++) {
		for (int x = 0; x < MapW; x++) {

			bool hasTile = false;
			for (int z = 0; z < 8; z++) {
				if (Tiles[x][y][z] != NULL) {
					hasTile = true;
					break;
				}
			}

			if (!hasTile) {

				int ren_x = (x * TileW) - CamX;
				int ren_y = (y * TileH) - CamY;
				Draw->DrawTex(ren_x, ren_y, TileW, TileH, HighLight, 0.2f, 0.2f, 0.2f, 1);

			}

		}
	}

	for (int z = 0; z < 8; z++) {
		for (int y = 0; y < MapH; y++) {

			for (int x = 0; x < MapW; x++) {

				int ren_x = (x * TileW) - CamX;
				int ren_y = (y * TileH) - CamY;



				MapTile* tile = Tiles[x][y][z];

				if (tile != NULL) {

					Texture2D* img = tile->GetImage();

					Draw->DrawTex(ren_x, ren_y, TileW, TileH, img, 1, 1, 1, 1);
					//printf("MapX:%d MapY:%d\n", ren_x, ren_y);
					//
				};
				if (z == 7) {

					if (Highlight[x][y])
					{
						Draw->DrawTex(ren_x, ren_y, TileW, TileH, HighLight, 1, 1, 1, 1);
					}

				}

			}

		}

	}
	*/

	
	Draw->End();

};

void Map::BakeShadows(int w,int h,float ba) {


	ShadowBaker* baker = new ShadowBaker();
	baker->SetSize(w, h);
	baker->SetMap(this);
	baker->SetUseGpu(true);
	baker->SetBlur(ba);
	baker->Bake();


}

void Map::Paste(MapTile* tile, int x, int y,int z) {

	Tiles[x][y][z] = tile;

}

void Map::ClearHighlight() {

	for (int y = 0; y < MapH; y++) {
		for (int x = 0; x < MapW; x++) {
			Highlight[x][y] = false;
		}
	}

}

void Map::SetHighlight(int x, int y, bool high) {

	Highlight[x][y] = high;

}