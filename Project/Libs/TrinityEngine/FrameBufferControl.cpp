#include "pch.h"
#include "FrameBufferControl.h"
#include "IDraw.h"
#include "Application.h"
FrameBufferControl::FrameBufferControl() {

	Buffer = NULL;
	PreBuffer = NULL;

};

void FrameBufferControl::Resized() {

	if (Buffer == NULL) {

		Buffer = new kFrameBuffer(GetW(), GetH());
		PreBuffer = new kFrameBuffer(GetW(), GetH());
		int w = GetW();
		int h = GetH();
	}
	else
	{
		delete Buffer;
		delete PreBuffer;
		Buffer = new kFrameBuffer(GetW(), GetH());
		PreBuffer = new kFrameBuffer(GetW(), GetH());
	
	}
//	int w = GetW();



	Draw = new IDraw(Application::WinW, Application::WinH);

};

void FrameBufferControl::Render() {

	//PreBuffer->bind();
	//RenderPreBuffer();
	//PreBuffer->unbind();
	Buffer->bind();
	RenderBuffer(PreBuffer);
	Buffer->unbind();
	IDraw* draw = GetDraw();
	draw->Begin();
	draw->DrawTex(GetX(), GetY(), GetW(), GetH(), Buffer->GetBB(), 1, 1, 1, 1);
	draw->End();




}