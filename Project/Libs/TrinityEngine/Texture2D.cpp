#include "pch.h"
#include "Texture2D.h"
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glew.h>
#include "Application.h"
#include "VFile.h"


Texture2D::Texture2D(VFile* fil) {

	Width = fil->ReadInt();
	Height = fil->ReadInt();
	Alpha = fil->ReadBool();

	int bpp = 3;
	if (Alpha) {
		bpp = 4;

	}

	int siz = Width * Height * bpp;

	Raw = (unsigned char *)fil->ReadBytes(siz);

	finish();

	loaded = true;
	binded = true;

}

Texture2D::Texture2D(unsigned char* data, int w, int h,bool alpha) {


	Width = (int)w;
	Height = (int)h;

	Alpha = alpha;
	
	Raw = data;


	glGenTextures(1, &ID);



	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (Alpha) {
		glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	
}

Texture2D::Texture2D(int w, int h, bool alpha) {

	Width = w;
	Height = h;
	Alpha = alpha;
	GLenum form = GL_RGB;
	int bpp = 3;
	if (alpha) {
		bpp = 4;
		form = GL_RGBA;
	}

	glGenTextures(1, &ID);



	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0,bpp, w, h, 0, form, GL_UNSIGNED_BYTE, NULL);
}

void Texture2D::LoadSub(char* buf) {


	glBindTexture(GL_TEXTURE_2D, ID);

	

	//GL.BindTexture(TextureTarget.Texture2D, ID);
	if (Alpha)
	{
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, buf);
		//GL.TexSubImage2D(TextureTarget.Texture2D, 0, 0, 0, W, H, PixelFormat.Rgba, PixelType.UnsignedByte, data);
	}
	else
	{
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, Width, Height, GL_RGB, GL_UNSIGNED_BYTE, buf);
	//	GL.TexSubImage2D(TextureTarget.Texture2D, 0, 0, 0, W, H, PixelFormat.Rgb, PixelType.UnsignedByte, data);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	//GL.BindTexture(TextureTarget.Texture2D, 0);



}

Texture2D::Texture2D(int w, int h) {

	Width = w;
	Height = h;

	glGenTextures(1, &ID);



	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB32F, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	loaded = true;
	binded = true;
};

void loadTex(Texture2D * tex) {
	int iw, ih, bpp, ds;
	ds = 0;
	const char* npath = tex->GetPath();
	unsigned char* raw;
	raw = stbi_load(npath, &iw, &ih, &bpp, ds);
	
	bool alpha = false;
	if (bpp == 4) {
		alpha = true;
	}
	tex->Set(iw, ih, alpha,raw);
	
	printf("Tex W:%d H:%d \n", iw, ih);

}

void StreamTex(Texture2D* tex) {

	VFile* nf = new VFile(tex->GetPath(), FileMode::Read);

	int Width = nf->ReadInt();
	int Height = nf->ReadInt();
	bool Alpha = nf->ReadBool();
	int bpp = 3;
	unsigned char* Raw;
	if (Alpha) {

		Raw = (unsigned char*)nf->ReadBytes(Width * Height * 4);
		bpp = 4;
	}
	else {
		bpp = 3;
		Raw = (unsigned char*)nf->ReadBytes(Width * Height * 3);

	}
	nf->Close();
	tex->Set(Width, Height, Alpha, Raw);
	
	//loaded = true;


}

Texture2D::Texture2D(const char* path, bool alpha, bool absPath)
{
	int iw, ih, bpp;
	printf("LoadTex:");
	printf(path);
	printf("\n");


	ID = 0;

	int ds = 3;

	if (alpha) {
		ds = 4;
	}


	if (!absPath) {
		const char* npath = Application::GetPath(path);

		texPath = npath;

	}
	else {
		texPath = path;
	}
	//iw = 0;
	//ih = 0;
//	bpp = 0;

	VString nn(texPath);
	nn.Add(".tc");

	this->texPath = nn.GetConst();

	if (VFile::Exists(nn.GetConst())) {
	

		std::thread stream(StreamTex, this);
		stream.detach();
		
		//finish();
	}
	else {

		loadTex(this);
		finish();
	
		VFile* nf = new VFile(nn.GetConst(), FileMode::Write);

		nf->WriteInt(Width);
		nf->WriteInt(Height);
		nf->WriteBool(Alpha);
		if (Alpha) {

			nf->WriteBytes(Raw, Width * Height * 4);

		}
		else {

			nf->WriteBytes(Raw, Width * Height * 3);

		}
		nf->Close();

	}
	//std::thread load(loadTex, this);
	//load.join();
	//load.join();

}

void Texture2D::UntilLoaded() {

	while (!loaded) {

	}

}

Texture2D::Texture2D(const char* path,bool alpha) {

	int iw, ih, bpp;
	
	ID = 0;

	int ds = 3;

	if (alpha) {
		ds = 4;
	}

	const char * npath = Application::GetPath(path);
	texPath = npath;
	
	//iw = 0;
	//ih = 0;
//	bpp = 0;

	std::thread load(loadTex, this);
	//load.join();
	load.detach();


};

Texture2D::~Texture2D() {

	glDeleteTextures(1, &ID);


};

void Texture2D::finish() {


	binded = true;
	glGenTextures(1, &ID);

	//printf("TEX - W:%d H:%d BPP:%d\n", iw, ih, bpp);



	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	GLenum form = GL_RGB;

	if (Alpha) {
		form = GL_RGBA;
	}
	int bpp = 3;
	if (Alpha) {
		bpp = 4;
	}

	float aniso;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);


	glTexImage2D(GL_TEXTURE_2D, 0, bpp, Width, Height, 0, form, GL_UNSIGNED_BYTE, Raw);

	//glBindTexture(GL_TEXTURE_2D, 0);


	glGenerateMipmap(GL_TEXTURE_2D);



	glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture2D::Bind(int unit) {

	if (loaded && !binded) {
		finish();
	}
	glActiveTexture(GL_TEXTURE0 + unit);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ID);

};

void Texture2D::Release(int unit) {

	glActiveTexture(GL_TEXTURE0 + unit);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);


};

int Texture2D::GetWidth() {

	return Width;

}

int Texture2D::GetHeight() {

	return Height;

}