#pragma once
#include "fmod.hpp"
//#include "common.h"
#include "SoundSource.h"
class SoundEngine
{
public:

	SoundEngine();
	SoundSource* LoadSound(const char* file);

private:

	FMOD::System *Sys;


};


