#pragma once
#include "FrameBufferControl.h"
#include "UIControl.h"
#include "Map.h"
#include "MapTile.h"
#include "kFrameBuffer.h"
class IDraw;


enum MapEditMode {

	Paste,Line,Rect,Circle,Clear,Fill

};

class MapEditControl :
	public FrameBufferControl
{
public:

	static MapTile* CurTile;

	MapEditControl(int mw, int mh, int tw, int th);

	void Resized();

	void RenderBuffer(kFrameBuffer * pre);
	void RenderPreBuffer();

	void MouseDown(int b);

	void MouseUp(int b);

	void MouseMove(int x, int y, int dx, int dy);

	static MapEditControl* Main;

	 void SetMode(MapEditMode m) {

		 mode = m;

	}

	 Map* GetMap() {

		 return CurMap;

	 }

	 void SetLayer(int l) {

		 CurrentLayer = l;

	 }

	 MapNode* GetActiveNode() {

		 return ActiveNode;

	 }
	 void SetChangedNode(std::function<void(MapNode* node)> changed) {

		 ChangedNode = changed;

	 }

	 void Render();

private:

	Map* CurMap;
	IDraw* Draw;
	bool Dragging = false;
	bool Rotating = false;
	bool Zooming = false;
	Texture2D* Frame;
	TileInfo* CurEdit;
	MapEditMode mode = MapEditMode::Paste;
	bool EditOn = false;
	bool OverUp, OverRight, OverRotate;
	bool MoveRight, MoveUp, Rotate;
	MapNode* ActiveNode = NULL;
	int CurrentLayer = 0;
	std::function<void(MapNode* node)> ChangedNode = NULL;
	kFrameBuffer* shadowBuf;

	kFrameBuffer* finalBuf;
};

