#include "pch.h"
#include "ParticleSystem.h"
#include "TMaths.h"
#include <cstdlib>

void updateParts(ParticleSystem* psys) {

	int a = 0;
	while (true) {
		//printf("!%d\n",a);
		psys->Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(35));
		//a++;

	}

}

ParticleSystem::ParticleSystem() {

	//Particles = NULL;
	//NextOne = NULL;
	Pool.resize(0);
	pCount = 0;


	std::thread update_parts(updateParts, this);
	update_parts.detach();
	


}

void ParticleSystem::AddToPool(ParticleBase* p) {

	Pool.push_back(p);

}

ParticleBase* ParticleSystem::GetLast() {

	return NULL;

}

void ParticleSystem::Spawn(int num,float x,float y) {

	

	for (int i = 0; i < num; i++) {
		for (int p = 0; p < Pool.size(); p++) {

			auto p1 = Pool[p];

			float ax = TMaths::Rnd(p1->MinX, p1->MaxX);
			float ay = TMaths::Rnd(p1->MinY, p1->MaxY);
			float az = TMaths::Rnd(p1->MinZ, p1->MaxZ);

			float ar = TMaths::Rnd(p1->MinR, p1->MaxR);
			float aa = TMaths::Rnd(p1->MinAlpha, p1->MaxAlpha);
			float al = TMaths::Rnd(p1->MinLife, p1->MaxLife);

			float aw = TMaths::Rnd(p1->MinW, p1->MaxW);
			float ah = TMaths::Rnd(p1->MinH, p1->MaxH);

			float axi = TMaths::Rnd(p1->MinXI, p1->MaxXI);
			float ayi = TMaths::Rnd(p1->MinYI, p1->MaxYI);
			float azi = TMaths::Rnd(p1->MinZI, p1->MaxZI);

			ParticleBase* np = new ParticleBase();
			np->X = x+ax;
			np->Y = y+ay;
			np->Z = az;

			np->Image = p1->Image;

			np->Rot = ar;
			np->Alpha = aa;
			np->Life = al;

			np->W = aw;
			np->H = ah;

			np->XI = axi;
			np->YI = ayi;
			np->ZI = azi;
				
			pmut.lock();
			Particles[pCount] = np;
			pCount++;
			pmut.unlock();
		
			/*
			//Particles.push_back(np);
			if (Particles == NULL) {
				Particles = np;
				NextOne = np;
			}
			else {
				NextOne->Next = np;
				NextOne = np;
			}
			*/




		}
	}

}

void ParticleSystem::Update() {

	//for(int i = 0; i < Particles.size(); i++) {

//	if (p1 == NULL) return;

	int ppc = 0;
	pmut.lock();
	while(true){
		
	

		auto ap = (ParticleBase*)Particles[ppc];
		
		if (ap == NULL) {
			ppc++;
			if (ppc >= pCount) {
				pmut.unlock();
				return;
			}
			continue;
		}

		ap->X += ap->XI;
		ap->Y += ap->YI;
		ap->Z += ap->ZI;

		ap->Rot += ap->RotI;
		ap->W += ap->wI;
		ap->H += ap->hI;

		ap->Alpha *= ap->AlphaI;
		ap->LifeI *= ap->LifeI;

		if (ap->Alpha <= 0.1f)
		{

			delete ap;
			if (pCount == 1) {
				Particles[0] = NULL;
				pCount = 0;
				
			}
			else {
				if (ppc == pCount - 1)
				{
					Particles[pCount - 1] = NULL;
					pCount--;

				}
				else {
					Particles[ppc] = Particles[pCount - 1];
					pCount--;
				}
			}

		}
		

		ppc++;
		if (ppc >= pCount) {
			pmut.unlock();
			return;
		}



	}

	pmut.unlock();

	//printf("Particles:%d---\n", ppc);

}