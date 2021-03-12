#pragma once
#include "AIState.h"
#include <vector>

class MapSprite;

class AIFSM
{
public:
	AIFSM() {
		States.resize(0);
	}
	AIFSM(const char* name,MapSprite* spr);
	void SetSprite(MapSprite* spr);
	void SetBaseState(AIState* state);
	void Start();
	void Update();
	AIState* FindState(const char* state);
	void SetState(AIState* state);
	void AddState(AIState* state);
	

private:
	const char* Name;
	std::vector<AIState* > States;
	AIState* BaseState;
	AIState* CurrentState;
	MapSprite* Spr;

};

