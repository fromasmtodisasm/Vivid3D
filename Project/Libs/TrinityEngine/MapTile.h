#pragma once
#include "Texture2D.h"
#include <vector>
class MapTile
{
public:

	MapTile(Texture2D* img);
	MapTile(const char* path);
	MapTile(MapTile* tile);
	MapTile();
	Texture2D* GetImage();
	Texture2D* GetNormal() {
		return Normal;
	}
	Texture2D* GetShadow() {
		return Shadow;
	}
	void SetImage(Texture2D* tex) {

		Image = tex;

	}
	void SetNormal(Texture2D* tex) {

		Normal = tex;

	}

	void SetShadow(Texture2D* tex) {

		Shadow = tex;

	}

	void Save();

	void SetT(float* tx, float* ty) {

		TX = tx;
		TY = ty;

	}

	float* GetTX() {
		return TX;
	}

	float* GetTY() {
		return TY;
	}

	bool* GetCastShadowsPtr() {

		return &CastShadows;

	}

	bool* GetColliderPtr() {

		return &Collider;
	}

	void SetCollider(bool v) {

		Collider = v;
	}

	void SetCastShadows(bool v) {

		CastShadows = v;

	}

	bool GetCollider() {
		return Collider;
	}
	bool GetCastsShadow() {
		return CastShadows;
	}
private:

	Texture2D* Image;
	Texture2D* Normal;
	Texture2D* Shadow;
	bool CastShadows = false;
	bool RecvShadows = true;
	bool Collider = false;
	float* TX;
	float* TY;
	std::vector<const char*> meta;
	char* DataPath;
};

