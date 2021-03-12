#pragma once
#include "Texture2D.h"
#include "Map.h"
class ShadowBaker
{
public:
	ShadowBaker();
	void SetSize(int w, int h);
	void SetMap(Map* m);
	void Bake();
	void SetUseGpu(bool s) {
		useGpu = s;
	}
	void SetBlur(float a) {
		Blur = a;
	}

private:
	float Blur = 0.01f;
	int texW, texH;
	unsigned char* buffer;
	Map* map;
	bool useGpu = false;
};

