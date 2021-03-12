#pragma once
#include <vector>
#include "ParticleBase.h"
#include "VList.h"
#include <thread>
#include <mutex>

const int MAXPARTS = 10000;

class ParticleSystem
{
public:
	ParticleSystem();
	void AddToPool(ParticleBase* p);
	void Spawn(int num,float x,float y);

	void Update();

	ParticleBase* GetLast();

	float X, Y, Z;


	//std::vector<ParticleBase*> Particles;

	//ParticleBase* Particles = NULL;
	//ParticleBase* NextOne = NULL;
	int pCount = 0;

	//VList<ParticleBase*> PList;
	void* Particles[MAXPARTS];


	std::vector<ParticleBase*> Pool;
	std::mutex pmut;

};

