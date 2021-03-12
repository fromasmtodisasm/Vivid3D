#pragma once
#include "Texture2D.h"

class ParticleBase
{
public:

	ParticleBase();
	void SetImage(Texture2D* img);
	void Update();

	void Copy(ParticleBase* p) {

		MinX = p->MinX;
		MinY = p->MinY;
		MinZ = p->MinZ;

		MaxX = p->MaxX;
		MaxY = p->MaxY;
		MaxZ = p->MaxZ;

		MinR = p->MinR;
		MaxR = p->MaxR;

		MinAlpha = p->MinAlpha;
		MaxAlpha = p->MaxAlpha;

		MinXI = p->MinXI;
		MaxXI = p->MaxXI;

		MinYI = p->MinYI;
		MaxYI = p->MaxYI;

		MinZI = p->MinZI;
		MaxZI = p->MaxZI;
		
		MinLife = p->MinLife;
		MaxLife = p->MaxLife;

		W = p->W;
		H = p->H;

		wI = p->wI;
		hI = p->hI;

		MinW = p->MinW;
		MaxW = p->MaxW;

		MinH = p->MinH;
		MaxH = p->MaxH;


	}

	
	//Current
	Texture2D* Image = NULL;
	float X, Y, Z;
	float Rot = 0;
	float W, H;
	float Alpha = 1.0f;
	float Life = 1.0f;

	//Attribs
	float XI, YI, ZI;
	float RotI;
	float wI, hI;
	float AlphaI;
	float LifeI;

	//Start
	float MinX, MaxX;
	float MinY, MaxY;
	float MinZ, MaxZ;

	float MinR, MaxR;
	float MinAlpha, MaxAlpha;
	float MinLife, MaxLife;
	float MinW, MaxW;
	float MinH, MaxH;

	float MinXI, MaxXI;
	float MinYI, MaxYI;
	float MinZI, MaxZI;

	ParticleBase* Next = NULL;
	ParticleBase* Prev;

};

