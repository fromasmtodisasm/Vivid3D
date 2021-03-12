#include "pch.h"
#include "AIFSM.h"
#include "VString.h"

AIFSM::AIFSM(const char* name,MapSprite* spr) {

	Name = name;
	Spr = spr;
	BaseState = NULL;
	CurrentState = NULL;

}

void AIFSM::SetSprite(MapSprite* spr) {

	Spr = spr;

}

void AIFSM::SetBaseState(AIState* state) {

	BaseState = state;
	BaseState->SetSprite(Spr);
	//state->SetOwner(this);

}

void AIFSM::Start() {

	SetState(BaseState);

}

void AIFSM::SetState(AIState* state) {

	CurrentState = state;
	CurrentState->SetSprite(Spr);
	CurrentState->Start();

}

AIState* AIFSM::FindState(const char* state) {

	for (int i = 0; i < States.size(); i++) {

		auto st = States[i];

		if (VString(state).IsSame(VString(st->GetName()))) {

			return st;

		}

	}

}

void AIFSM::AddState(AIState* state) {

	States.push_back(state);

}

void AIFSM::Update() {

	if (CurrentState != NULL) {

		CurrentState->Update();
		if (CurrentState->GetChangeState()) {


		
			AIState* next = FindState(CurrentState->GetNextState());
			CurrentState->Stop();
			SetState(next);

			return;
		
		}

	}

}