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
	RenderPreBuffer();
	// 
	//PreBuffer->unbind();
	glViewport(0, 0, GetW(), GetH());
	Buffer->bind();
	RenderBuffer(PreBuffer);
	Buffer->unbind();
	IDraw* draw = GetDraw();
	glViewport(0, 0, Application::WinW, Application::WinH);
	draw->Begin();
	draw->DrawTex(GetX(), GetY()+GetH(), GetW(), -GetH(), Buffer->GetBB(), 1, 1, 1, 1);
	draw->End();




}