#pragma once
#include <GL/glew.h>
#include "Texture2D.h"
#include <stdio.h>

class kFrameBuffer
{
public:
	kFrameBuffer(int w, int h);
	~kFrameBuffer();
	void bind();
	void unbind();
	Texture2D* GetBB();

private:
//	~kFrameBuffer();

	int fW, fH;
	GLuint id;
	GLuint rb;
	Texture2D* bb;


};

