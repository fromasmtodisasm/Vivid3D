#pragma once
#include "Application.h"
#include "UI.h"
#include "UIControl.h"
#include "ButtonControl.h"
#include "WindowControl.h"
#include "VerticalSplitterControl.h"
#include "HorizontalSplitterControl.h"
#include "MapEditControl.h"
#include "kFrameBuffer.h"
#include "NodeServer.h"
class TileSetApp : public Application
{

public:

	TileSetApp();

	void Init();
	void Update();
	void Render();
	bool previewMode = false;
	static TileSetApp* Main;
	static NodeServer* NodeServe;
private:

	kFrameBuffer* shadowBuf;
	UI* ui;


	


};


