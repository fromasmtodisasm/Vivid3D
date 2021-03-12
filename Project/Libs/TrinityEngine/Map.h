#pragma once

#include "MapTile.h"
#include "MapLight.h"
#include "FXLight2D.h"
#include "VFile.h"
#include "VString.h"
#include <chipmunk.h>
#include "MapNode.h"
#include "MapSprite.h"
#include "kFrameBuffer.h"
#include "FXShadow2D.h"
#include "FXPreShadow2D.h"
#include "ParticleSystem.h"
#include "FXSoftParticle2D.h"
#include "FXLightMap2D.h"
#include "Mesh2D.h"
#include "MapDecal.h"

class IDraw;

const int MAX_W = 512;
const int MAX_H = 512;
const int MAX_D = 8;

struct TileInfo {

	int TileX, TileY, TileZ;
	MapTile* Tile[16];
	MapNode* Node;

	bool Up, Right, Rotate;

};

struct HitInfo {

	int TileX, TileY, TileZ;
	float HitX, HitY;
	float NX, NY;
	float PA;
	bool Hit;
	float dis;
	float sx, sy;
	cpShape* shape;
	MapSprite* spr;

};

struct PixelInfo {

	int colR, colG, colB;
	bool shadowCaster;

};

struct SeeInfo {

	std::vector<MapSprite*> sprites;
	bool seen;

};


class Map
{
public:

	Map(int w, int h, int tw, int th,float gx=0,float gy=0);

	HitInfo Raycast(float x, float y, float x1, float y1);
	

	void SetTile(int x, int y, int z, MapTile* tile);

	void SetDraw(int w, int h);

	void SetHighlight(int x, int y, bool high);

	void Move(float x, float y);

	void Turn(float a);

	void Zoom(float a);

	MapSprite* GetSpriteWithShape(cpShape* s) {

		for (int i = 0; i < Sprites.size(); i++) {

			auto spr = Sprites[i];

			if (s == spr->GetShape()) {
				return spr;
			}

		}
		return NULL;
	}

	TileInfo* TileAt(int x, int y);

	void ClearHighlight();

	void Render();

	void RenderDecal(MapDecal* d);

	void RenderDeferred();


	void RenderShadows1();
	void RenderShadows2(Texture2D* bb);

	void Fill(MapTile* tile, int z = 0);

	void Paste(MapTile* tile, int x, int y,int z=0);
	void SetShadowMap(Texture2D* tex) {
		ShadowMap = tex;
	}
	void SetActiveNode(MapNode* node) {
		ActiveNode = node;
	}
	MapNode* GetActiveNode() {
		return ActiveNode;
	}
	
	bool PointInNode(float x, float y,int mx,int my);
	void RenderTexture(Texture2D* tex, float x, float y,float r = -1,float cr=1,float cg=1,float cb=1);

	void RenderNode(MapNode* node,float r=1,float g=1,float b=1);
	void RenderSpriteNormal(MapSprite* s)
	{}
	void RenderSprite(MapSprite* s);


	void SetCam(float x, float y, float z = 1.0f)
	{
		CamX = x;
		CamY = y;
		CamZ = z;
	}


	float GetRot() {

		return CamRot;

	}
	void SetRot(float r) {
		CamRot = r;
	}

	std::vector<MapLight*> GetLights() {

		return Lights;

	}

	std::vector<MapNode*> GetNodes() {

		return Nodes;

	}

	void AddDecal(MapDecal* dec) {

		Decals.push_back(dec);

	}

	void AddSprite(MapSprite* spr) {
		Sprites.push_back(spr);
	}

	void LoadMap(const char* map) {


		VString nmap = VString(map);

		nmap.Replace("\n"[0], "\0"[0]);

		map = nmap.GetConst();

		Lights.resize(0);
		Nodes.resize(0);

		VFile* f = new VFile(map, FileMode::Read);

		int lc = f->ReadInt();

		for (int i = 0; i < lc; i++) {

			auto l = new MapLight();
			Lights.push_back(l);
			Nodes.push_back(l);
			l->SetIcon(LightIcon);

			Vec3 pos = f->ReadVec3();
			Vec3 diff = f->ReadVec3();
			float range = f->ReadFloat();
			bool gs = f->ReadBool();
			float sa = f->ReadFloat();
			float sd = f->ReadFloat();
			bool dyn = f->ReadBool();
			if (dyn) {


			}
			else {

				Texture2D* bs = new Texture2D(f);
				l->SetBakedShadows(bs);
			}


			l->SetDiffuse(diff);
			l->SetPos(pos);
			l->SetRange(range);
			l->SetSpot(gs);
			l->SetSpotDir(sd);
			l->SetSpotAngle(sa);

		}

		int nc = f->ReadInt();

		for (int i = 0; i < nc; i++) {

			MapNode* nn = new MapNode();
			Vec3 pos = f->ReadVec3();
			float rt = f->ReadFloat();
			const char* name = f->ReadString();
			const char* imgp = f->ReadString();
			int nw, nh;
			nw = f->ReadInt();
			nh = f->ReadInt();
			nn->SetPos(pos);
			nn->SetName(name);
			nn->SetSize(nw, nh);
			nn->SetRot(rt);
			nn->CreateBoxPhysics(this->GetSpace(),0.1f);
			nn->SetImage(new Texture2D(imgp, true, true));
			const char* spath;
			if (f->ReadBool()) {

				spath = f->ReadString();

			}

			Nodes.push_back(nn);
			printf("Node Load:");
			printf(name);
			printf("\n");
			nn->AlignPhysics();
		}

		int tc = f->ReadInt();

		std::vector<MapTile*> tl;

		tl.resize(0);

		for (int i = 0; i < tc; i++) {

			MapTile* tile = new MapTile();

			auto col = new Texture2D(f);
			auto norm = new Texture2D(f);
			auto shad = new Texture2D(f);

			tile->SetImage(col);
			tile->SetNormal(norm);
			tile->SetShadow(shad);
			tile->SetCollider(f->ReadBool());
			tile->SetCastShadows(f->ReadBool());
		
			tl.push_back(tile);

		}


		MapW = f->ReadInt();
		MapH = f->ReadInt();
		TileW = f->ReadInt();
		TileH = f->ReadInt();

		for (int z = 0; z < MAX_D; z++) {
			for (int y = 0; y < MAX_H; y++) {
				for (int x = 0; x < MAX_W; x++) {

					bool it = f->ReadBool();

					if (it == NULL) {

						Tiles[x][y][z] = NULL;

					}
					else {

						int tid = f->ReadInt();
						Tiles[x][y][z] = tl[tid];

					}

				}
			}
		}

		f->Close();

	}

	void BakeShadows(int w,int h,float blur);

	void SaveMap(const char* map) {

		VString nmap = VString(map);

		nmap.Replace("\n"[0], "\0"[0]);

		map = nmap.GetConst();

		VFile* f = new VFile(map, FileMode::Write);

		f->WriteInt(Lights.size());
		for (int i = 0; i < Lights.size(); i++) {

			auto l = Lights[i];

			Vec3 pos = l->GetPos();
			Vec3 diff = l->GetDiffuse();
			float range = l->GetRange();

			f->WriteVec3(pos);
			f->WriteVec3(diff);
			f->WriteFloat(range);
			f->WriteBool(l->GetSpot());
			f->WriteFloat(l->GetSpotAngle());
			f->WriteFloat(l->GetSpotDir());
			f->WriteBool(l->GetDynamic());
			if (l->GetDynamic()) {

			}
			else {
				l->GetBakedShadows()->Write(f);
			}
		}

		int nc = 0;
		for (int i = 0; i < Nodes.size(); i++) {

			if (Nodes[i]->GetType() == NodeType::TypeNode) {
				nc++;
			}

		}

		f->WriteInt(nc);

		for (int i = 0; i < Nodes.size(); i++) {

			if (Nodes[i]->GetType() == NodeType::TypeNode)
			{

				Vec3 pos = Nodes[i]->GetPos();
				float r = Nodes[i]->GetRot();
				const char* name = Nodes[i]->GetName();

				f->WriteVec3(pos);
				f->WriteFloat(r);
				f->WriteString(name);
				Texture2D* img = Nodes[i]->GetImage();
				f->WriteString(img->GetPath());
				f->WriteInt(Nodes[i]->GetW());
				f->WriteInt(Nodes[i]->GetH());
				
				if (Nodes[i]->GetLS() != NULL) {

					f->WriteBool(true);
					f->WriteString(Nodes[i]->GetLS()->GetPath());

				}
				else {
					f->WriteBool(false);
				}


			}

		}

		std::vector<MapTile*> tiles;

		tiles.resize(0);

		for (int z = 0; z < MAX_D; z++) {
			for (int y = 0; y < MAX_H; y++) {
				for (int x = 0; x < MAX_W; x++) {

					MapTile* tile = Tiles[x][y][z];
					if (tile != NULL) {
						if (tiles.size() == 0) {
							tiles.push_back(tile);
						}
						else {

							bool already = false;
							for (int i = 0; i < tiles.size(); i++) {

								if (tiles[i] == tile) {
									already = true;
									break;
								}

							}

							if (!already) {

								tiles.push_back(tile);

							}

						}
					}

				}
			}
		}

		f->WriteInt(tiles.size());

		for (int i = 0; i < tiles.size(); i++) {

			auto tile = tiles[i];

			
			tile->GetImage()->Write(f);
			tile->GetNormal()->Write(f);
			tile->GetShadow()->Write(f);

			f->WriteBool(tile->GetCollider());
			f->WriteBool(tile->GetCastsShadow());

		};


		f->WriteInt(MapW);
		f->WriteInt(MapH);
		f->WriteInt(TileW);
		f->WriteInt(TileH);

		for (int z = 0; z < MAX_D; z++) {

			for (int y = 0; y < MAX_H; y++) {

				for (int x = 0; x < MAX_W; x++) {

					auto tile = Tiles[x][y][z];

					if (tile == NULL) {

						f->WriteBool(false);

					}
					else {

						f->WriteBool(true);
						for (int i = 0; i < tiles.size(); i++) {

							auto t2 = tiles[i];

							if (t2 == tile) {
								f->WriteInt(i);

							}


						}

					}

				}
			}
		}

		f->Close();

	};
	void SetGameMode(bool gm) {
		gameMode = gm;
	}

	void AddNode(MapNode* node) {

		Nodes.push_back(node);

	}

	void AddLight(MapLight* l) {

		Nodes.push_back(l);
		Lights.push_back(l);

	}

	int GetW() {

		return TileW * MapW;

	}

	int GetH() {

		return TileH * MapH;

	}

	PixelInfo GetPixelInfo(int x, int y) {

		int tx = x / TileW;
		int ty = y / TileH;

		int bx = tx * TileW;
		int by = ty * TileH;

		int ax = x - bx;
		int ay = y - by;

	//	printf("AX:%d AY:%d \n", ax, ay);

		int tr, tg, tb;
		tr = 0;
		tg = 0;
		tb = 0;
		bool shadow = false;

		for (int z = 0; z < 4; z++) {

			MapTile* tile = Tiles[tx][ty][z];
			if (tile != NULL) {

				auto tex = tile->GetImage();
				
				auto raw = tex->GetRaw();

				float xR = (float)(tex->GetWidth()) / (float)(TileW);
				float yR = (float)(tex->GetHeight()) / (float)(TileH);
				
				int texX = ax * xR;
				int texY = ay * yR;

				int bpp = 3;

				if (tex->GetAlpha()) {
					bpp = 4;
				}

				int loc = (texY * tex->GetWidth() * bpp) + texX * bpp;

				tr = raw[loc];
				tg = raw[loc + 1];
				tb = raw[loc + 2];

				if (tile->GetCastsShadow()) {

					shadow = true;

				}

				//int loc = 



			}

		}

		PixelInfo pix;

		pix.colR = tr;
		pix.colG = tg;
		pix.colB = tb;
		pix.shadowCaster = shadow;

		return pix;

	}

	cpSpace* GetSpace() {

		return pSpace;

	}

	void UpdateMap() {

		for (int i = 0; i < Sprites.size(); i++) {

			auto s = Sprites[i];

			s->UpdateSprite();

			if (s->IsAlive() == false && s->AIExists()) {

				s->DisableAI();
				//Sprites.erase(Sprites.begin() + i);
				return;

			}

		}
	}

	SeeInfo See(float x, float y, float a, float fov, float r, MapSprite* exclude)
	{

		SeeInfo info;
		info.seen = false;
		info.sprites.resize(0);

		for (int i = 0; i < Sprites.size(); i++) {

			auto s = Sprites[i];
			if (s == exclude) continue;

			Vec3 sp = s->GetPos();

			float xd = sp.X - x;
			float yd = sp.Y - y;

			float ang = atan2(yd, xd);
			ang = TMaths::RadToDeg(ang);

			if (ang < 0.0f)
			{
				ang = 360.f + ang;
			}
			if (ang > 360.f)
			{
				ang = ang - 36.0f;
			}

			float a1 = TMaths::Max(a, ang) - TMaths::Min(a, ang);
			float a2 = TMaths::Min(a, ang) + (360.0 - TMaths::Max(a, ang));
			float fv = 0;
			if (a1 < a2) {
				fv = a1;
			}
			else {
				fv = a2;
			}

			

			if (fv < fov) {

				float mag = sqrt(xd * xd + yd * yd);

				if (mag < r) {
					info.sprites.push_back(s);
					info.seen = true;
				}
			}

		}
		return info;
	}
	


	


	void RemoveLight(MapLight* l) {

		for (int i = 0; i < Lights.size(); i++) {
			if (Lights[i] == l) {
				Lights.erase(Lights.begin()+i);
			}
		}

		for (int i = 0; i < Nodes.size(); i++) {

			if (Nodes[i] == l) {

				Nodes.erase(Nodes.begin() + i);

			}

		}

	}

	void EnableColliders() {

		for (int y = 0; y < MapH; y++) {
			for (int x = 0; x < MapW; x++) {
				if (Tiles[x][y][0] == NULL) continue;
				if (Tiles[x][y][0]->GetCollider()) {


					int sx = x * TileW;
					int sy = y * TileH;

					cpShape* l1;
					cpShape* l2;
					cpShape* l3;
					cpShape* l4;

					//	l1 = cpSegmentShapeNew(cpSpaceGetStaticBody(pSpace), cpv(sx, sy), cpv(sx + TileW, sy), 0);
					//	l2 = cpSegmentShapeNew(cpSpaceGetStaticBody(pSpace), cpv(sx, sy), cpv(sx, sy + TileH), 0);
					//	l3 = cpSegmentShapeNew(cpSpaceGetStaticBody(pSpace), cpv(sx + TileW, sy), cpv(sx + TileW, sy + TileH), 0);
					//	l4 = cpSegmentShapeNew(cpSpaceGetStaticBody(pSpace), cpv(sx, sy + TileH), cpv(sx + TileW, sy + TileH), 0);

					cpBB bb;

					MapTile* t1 = Tiles[x][y][0];

					auto img = t1->GetImage();

					auto w = img->GetWidth();
					auto h = img->GetHeight();
					auto rgb = img->GetRaw();

				
						int lx = 2000;
						int ly = 2000;
						int bx = -2000;
						int by = -2000;
						int cx, cy;
						int loc = 0;
						if (img->GetAlpha()) {

						for (cy = 0; cy < h; cy++) {
							for (cx = 0; cx < w; cx++) {


								int alpha = (int)rgb[loc + 3];

								if (alpha > 0)
								{

									if (cx < lx) lx = cx;
									if (cy < ly) ly = cy;
									if (cx > bx) bx = cx;
									if (cy > by) by = cy;

								}



								loc = loc + 4;
							}
						}

					}
					else {
						lx = 0;
						ly = 0;
						bx = w;
						by = h;
					}
					float rx = (float)TileW/(float)w;
					float ry = (float)TileH/(float)h;

					lx = (float)(lx) * rx;
					ly = (float)(ly) * ry;
					bx = (float)(bx) * rx;
					by = (float)(by) * ry;
			
					//printf("IW:%d IH:%d RGB:%d", img->GetWidth(), img->GetHeight(), (int)img->GetRaw()[0]);
					//while (true) {

					//}

					printf("LX:%d LY:%d BX:%d BY:%d\n", lx, ly, bx, by);
					bb = cpBBNew(sx+lx,sy+by,sx+bx,sy+ly );// sx, sy + TileH, sx + TileW, sy);

					cpShape* s1 = cpBoxShapeNew2(cpSpaceGetStaticBody(pSpace),bb, 0);

				

					cpShapeSetFriction(s1, 0.2f);

					cpSpaceAddShape(pSpace, s1);


				}
			}
		}
	

	}

	Vec3 GetCam() {
		return Vec3(CamX, CamY, CamZ);
	}

	void RenderNodeShadow(MapNode* n);

	void UpdatePhysics() {

		cpFloat timeStep = 1.0 / 60.0;

		timeStep *= 6;


	//	for (cpFloat time = 0; time < 2; time += timeStep) {
			//	cpVect pos = cpBodyGetPosition(ballBody);
			//	cpVect vel = cpBodyGetVelocity(ballBody);
			//	printf(
			//		"Time is %5.2f. ballBody is at (%5.2f, %5.2f). It's velocity is (%5.2f, %5.2f)\n",
			//		time, pos.x, pos.y, vel.x, vel.y
			//	);
		for (int i = 0; i < Sprites.size(); i++) {

			auto n = Sprites[i];
			if (n->GetPhysics()) {

				Vec3 pos = n->GetPhysicsPos();
				//	printf("X:%f Y:%f Z:%f \n", pos.X, pos.Y, pos.Z);

				pos.Y = pos.Y;
				pos.X = pos.X;

				n->SetPos(pos);
				//n->SetRot(n->GetPhysicsRot());
				//n->SetRot(n->GetPhysicsRot());



			}

		}
			for (int i = 0; i < Nodes.size(); i++) {

				auto n = Nodes[i];

				if (n->GetPhysics()) {

					Vec3 pos = n->GetPhysicsPos();
				//	printf("X:%f Y:%f Z:%f \n", pos.X, pos.Y, pos.Z);

					pos.Y = pos.Y;
					pos.X = pos.X;

					n->SetPos(pos);
					n->SetRot(n->GetPhysicsRot());
					//n->SetRot(n->GetPhysicsRot());



				}

			}

			cpSpaceStep(pSpace, timeStep);
	//	}
	//	while (true) {};
	}

	void AddParticleSystem(ParticleSystem* sys) {
		PSystems.push_back(sys);
	}

	void RenderParticles();
	void UpdateParticles();

	void Compile();
	void RenderCompiled();
	void RemoveSprite(MapSprite* spr) {

		for (int i = 0; i < Sprites.size(); i++) {

			if (Sprites[i] == spr) {
				Sprites.erase(Sprites.begin() + i);
				return;
			}

		}

	}

	static cpSpace* CurSpace;

	MapTile* Tiles[MAX_W][MAX_H][MAX_D];
	float* TileX[MAX_W][MAX_H];
	float* TileY[MAX_W][MAX_H];
	bool Highlight[MAX_W][MAX_H];
	int MapW, MapH;
	int TileW, TileH;
	float CamX, CamY, CamZ = 1.0f;
	float CamRot = 0.0f;
	IDraw* Draw = NULL;
	int DX, DY;
	Texture2D* HighLight;
	Texture2D* NoTile;
	Texture2D* LightIcon;
	Texture2D* White;
	Texture2D* Circle;
	std::vector<MapLight*> Lights;
	std::vector<MapNode*> Nodes;
	std::vector<MapSprite*> Sprites;
	std::vector<MapDecal*> Decals;
	FXLight2D* lightFx;
	FXShadow2D* shadowFx;
	FXPreShadow2D* preShadowFx;
	FXSoftParticle2D* particleFx;
	FXLightMap2D* lightMapFx;
	Texture2D* BlankNorm;
	Texture2D* ShadowMap;
	Texture2D* LeftRight;
	Texture2D* UpDown;
	Texture2D* Rotate;
	MapNode* ActiveNode = NULL;
	bool gameMode = false;
	cpSpace* pSpace;
	kFrameBuffer* dColor;
	kFrameBuffer* dNormal;
	float* rx;
	float* ry;
	std::vector<ParticleSystem*> PSystems;
	Mesh2D* CompiledMesh = NULL;
	Mesh2D* ShadowMesh = NULL;
	Mesh2D* CompiledMeshStatic = NULL;
	Mesh2D* ShadowMesh2 = NULL;
};

