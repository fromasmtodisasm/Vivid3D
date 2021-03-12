#include "pch.h"
#include "MapEditControl.h"
#include "IDraw.h"
#include "UI.h"
#include "kFrameBuffer.h"
MapEditControl::MapEditControl(int mw, int mh, int tw, int th) {

	SetText("MapEdit:/n");
	CurMap = new Map(mw, mh, tw, th);
	MapTile* noTile = new MapTile(new Texture2D("Edit/notile.png",true));
	Frame = new Texture2D("Edit/frame1.png", true);
	//CurMap->SetTile(1, 0,0, noTile);
	OverUp = false;
	OverRight = false;
	MoveUp = false;
	MoveRight = false;
	Rotate = false;



	for (int y = 0; y < mh; y++) {

		for (int x = 0; x < mw; x++) {

			//CurMap->SetTile(x, y,0, noTile);

		}
	}
	Main = this;
	CurMap->SetHighlight(0, 0, true);


}

void MapEditControl::MouseDown(int b) {

	if (b == 1) {
		Dragging = true;
		//	exit(1);
	}
	if (b == 2) {
		Rotating = true;
	}
	if (b == 0) {

		if (OverRight) {
			MoveRight = true;
			return;
		}
		if (OverUp) {
			MoveUp = true;
			return;
		}
		if (OverRotate) {
			Rotate = true;
			return;
		}


		switch (mode) {
		case MapEditMode::Fill:
			CurMap->Fill(CurTile, 0);
			break;
		default:
			EditOn = true;
			break;
		}

		if (CurEdit != NULL) {
			if (CurEdit->Node != NULL) {
				//exit(1);

				CurMap->SetActiveNode(CurEdit->Node);
				ActiveNode = CurEdit->Node;
				if (ChangedNode != NULL) {
					ChangedNode(ActiveNode);
				}
				EditOn = false;
			}
			else {
				CurMap->SetActiveNode(NULL);
			}
		}
	}
};

void MapEditControl::MouseUp(int b) {

	MoveUp = false;
	MoveRight = false;
	Rotate = false;
	if (b == 1) {
		Dragging = false;
	//	exit(1);
	}
	if (b == 2) {
		Rotating = false;
	}
	if (b == 0) {
		switch (mode) {
		case MapEditMode::Fill:
			break;
		default:
			EditOn = false;
			break;
		}
		
	}
};

void MapEditControl::MouseMove(int x, int y, int dx, int dy)
{

	float tW = GetW();
	float aW = Application::WinW;
	float tH = GetH();
	float aH = Application::WinH;

	float xR = aW / tW;
	float yR = aH / tH;

	x = x * xR;
	y = y * yR;
	
	float mx = 0;
	float my = 0;
	if (MoveUp) {
		
		my = dy;

	}
	if (MoveRight) {
		mx = dx;
	}
	
	if (Rotate) {

	//	mx = dx;
		auto an = CurMap->GetActiveNode();
		if (an != NULL) {
			an->Turn(dx);
		}

	}

	auto act = CurMap->GetActiveNode();

	if (act!= NULL) {

		auto p = act->GetPos();

		p.X = p.X + mx;
		p.Y = p.Y + my;

		act->SetPos(p);

	}

	//exit(1);
	if (Rotating == true && Dragging == true) {
		CurMap->Zoom(dy);
	}
	else {
		if (Dragging) {
			CurMap->Move(-dx, -dy);
		}
		if (Rotating)
		{
			CurMap->Turn(dx);
		}
	}

	if (EditOn) {

		if (CurEdit->TileX >= 0 && CurEdit->TileY >= 0) {
			switch (mode) {
			case MapEditMode::Paste:

				CurMap->Paste(CurTile, CurEdit->TileX, CurEdit->TileY,CurrentLayer);

				break;
			case MapEditMode::Clear:

				CurMap->Paste(NULL, CurEdit->TileX, CurEdit->TileY,CurrentLayer);

				break;

			}
		}
	}

	CurMap->ClearHighlight();
	if (CurEdit != NULL) {
		delete CurEdit;
	}

	CurEdit = NULL;
	TileInfo* info = CurMap->TileAt(x, y);
	CurEdit = info;

	printf("AtX:%d AtY:%d \n", info->TileX, info->TileY);

	if (CurEdit->Right) {
		OverRight = true;
	}
	else {
		OverRight = false;
	}

	if (CurEdit->Up) {
		OverUp = true;
	}
	else {
		OverUp = false;
	}
	if (CurEdit->Rotate) {
		OverRotate = true;
	}
	else {
		OverRotate = false;
	}

	if (info->Node == NULL && info->Up == false && info->Right == false && info->Rotate ==false) {
		if (info->TileX != -1) {

			CurMap->SetHighlight(info->TileX, info->TileY, true);
			//printf("HX:%d HY:%d\n MX:%d\n", info->TileX, info->TileY, x);
		}
	}

	//delete info;
}



void MapEditControl::Resized() {

	//FrameBufferControl::Resized();

	CurMap->SetDraw(GetW(), GetH());

	shadowBuf = new kFrameBuffer(GetW(), GetH());
	finalBuf = new kFrameBuffer(GetW(), GetH());

	Draw = new IDraw(GetW(), GetH());

}

void MapEditControl::RenderPreBuffer() {

	//CurMap->RenderShadows1();
	

}

MapEditControl* MapEditControl::Main = NULL;

void MapEditControl::Render() {


	/*
	shadowBuf->bind();
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	CurMap->RenderShadows1();
	shadowBuf->unbind();
	CurMap->RenderShadows2(shadowBuf->GetBB());
	*/

	finalBuf->bind();
	CurMap->Render();
	finalBuf->unbind();



	Draw->SingleDrawTex(GetX(), GetY() + GetH(), GetW(), -GetH(),finalBuf->GetBB(), 1, 1, 1, 1);

};


void MapEditControl::RenderBuffer(kFrameBuffer* pre) {

	CurMap->SetShadowMap(pre->GetBB());
	CurMap->Render();
	

	UI::DrawTexture(Frame, GetX() + 10, GetY() + GetH()-160, 200, 150, 1, 1, 1, 0.4f);
	if (CurTile!= NULL) {
		UI::RenderText(GetX() + 30+64, GetY() + GetH()-145, "Tile\n", 1, 1, 1, 1);
		UI::DrawTexture(CurTile->GetImage(), GetX() + 20, GetY() + GetH()-150, 64, 64, 1, 1, 1, 0.7f);
	}
};


MapTile* MapEditControl::CurTile = NULL;