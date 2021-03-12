#include "pch.h"
#include "AIState.h"

void AIState::Start() {

}

void AIState::Update() {


}

bool AIState::GetChangeState() {

	return ChangeState;

}

const char* AIState::GetNextState() {

	return NextState;

}

const char* AIState::GetName() {

	return Name;

}

void AIState::Stop() {

	ChangeState = false;
	NextState = "";

}

void AIState::SetSprite(MapSprite* spr) {
	Spr = spr;
}

/*
void AIState::SetOwner(AIFSM* owner) {

	Owner = owner;

}

*/