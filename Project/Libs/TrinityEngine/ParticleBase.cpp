#include "pch.h"
#include "ParticleBase.h"

ParticleBase::ParticleBase() {

	X = Y = 0;
	Z = 1.0f;
	Alpha = 1.0f;
	Rot = 0;
	W = 16;
	H = 16;
	Life = 1.0f;

	XI = YI = ZI = 0;
	AlphaI = 0.9f;
	LifeI = 0.98f;
	RotI = 0.0f;
	wI = 0;
	hI = 0;

};

void ParticleBase::SetImage(Texture2D* img) {

	Image = img;

}

void ParticleBase::Update() {

	X = X + XI;
	Y = Y + YI;
	Z = Z + ZI;
	Rot = Rot + RotI;
	Alpha = Alpha * AlphaI;
	Life = Life * LifeI;
	W = W + wI;
	H = H + hI;

}