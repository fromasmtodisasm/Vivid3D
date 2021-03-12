#include "pch.h"
#include "kFrameBuffer.h"
#include "Application.h"

kFrameBuffer::kFrameBuffer(int w,int h) {

	w = Application::WinW;
	h = Application::WinH;
	
	fW = w;
	fH = h;
	bb = new Texture2D(w, h);

	glGenFramebuffers(1, &id);

	glBindFramebuffer(GL_FRAMEBUFFER, id);

	glGenRenderbuffers(1, &rb);

	glBindRenderbuffer(GL_RENDERBUFFER, rb);

	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT32F_NV, fW, fH);

	

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, bb->GetID(), 0);


	GLenum db = (GLenum)GL_COLOR_ATTACHMENT0;


	glDrawBuffers(1, &db);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("Framebuffer faliure.\n");
	}
	else {
		printf("Framebuffer success.\n");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);


}

void kFrameBuffer::bind() {

	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glViewport(0, 0, fW, fH);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Application::SetRen(fW, fH);

}

void kFrameBuffer::unbind() {

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	Application::ResetRen();
}


Texture2D * kFrameBuffer::GetBB() {

	return bb;

}

kFrameBuffer::~kFrameBuffer() {

	glDeleteFramebuffers(1, &id);
	glDeleteRenderbuffers(1, &rb);
	delete bb;

}