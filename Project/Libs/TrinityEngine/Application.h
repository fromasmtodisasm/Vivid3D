#pragma once
//#include "pch.h"
#include <stack>
#include "AppState.h"
#include "SoundEngine.h"
class GLFWwindow;
#include <CL\cl.hpp>
#include "VirtualFileSystem.h"


class Application
{
public:

	Application();

	void CrWindow(int w, int h, const char* title);

	virtual void Init() {};
	virtual void Update() {};
	virtual void Render() {};

	int Width();
	int Height();

	static void SetRen(int w, int h);
	static void ResetRen();

	void InitCL();

	static int WinW;
	static int WinH;
	static int RenW;
	static int RenH;
	
	static const char* GetPath(const char* content);
	static const char* ContentPath;
	void Run();

	void PushState(AppState* state);
	void PopState();

	static Application* Main;


	AppState* GetState() {

		if (states.size() == 0) return NULL;
		return states.top();


	}

	void CreateSoundEngine() {

		SEngine = new SoundEngine();

	}

	SoundEngine* GetSoundEngine() {

		return SEngine;
	}

	cl::Context GetCLContext() {
		return clContext;
	}
	cl::Device GetCLDevice() {
		return clDevice;
	}

	void SetFileSystem(const char* basepath) {

		FileSys = new VirtualFileSystem(basepath);
		FileSys->ScanBase();

	}

	static AppState* InitialState;

	static void Resized(int w, int h);
	void SetSize(int w, int h);

private:
	GLFWwindow* Window;
	int WinWidth, WinHeight;
	int RenWidth, RenHeight;
	std::stack<AppState*> states;
	SoundEngine* SEngine;
	bool CLInit = false;
	cl::Platform clPlatform;
	cl::Device clDevice;
	cl::Context clContext;
	VirtualFileSystem* FileSys;
	
};

