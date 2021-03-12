#pragma once

class MapSprite;

class AIState
{
public:
	
	virtual void Start();
	virtual void Stop();
	virtual void Update();
	bool GetChangeState();
	const char* GetNextState();
	const char* GetName();
	void SetSprite(MapSprite* spr);

	//void SetOwner(AIFSM* owner);
protected:
	const char* Name;
	const char* NextState;
	bool ChangeState = false;
	MapSprite* Spr;
//	AIFSM* Owner;
};

