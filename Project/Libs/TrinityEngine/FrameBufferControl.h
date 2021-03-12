#pragma once
#include "UIControl.h"
#include "kFrameBuffer.h"

class IDraw;

class FrameBufferControl : public UIControl
{
public:

	FrameBufferControl();
	void Resized();
	void Render();
	virtual void RenderBuffer(kFrameBuffer* pre) {};
	virtual void RenderPreBuffer() {};
	IDraw* GetDraw() {
		return Draw;
	}
protected:

	IDraw* Draw;
	kFrameBuffer* Buffer = NULL;
	kFrameBuffer* PreBuffer = NULL;
	//std::function<void(int, int)> bufRen;

};

