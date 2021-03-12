#pragma once
class AppState
{
public:
	virtual void Init() {};
	virtual void Update() {};
	virtual void Render() {};
	virtual void Resized(int w, int h) {};


private:
	const char* Name;
};


