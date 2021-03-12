#pragma once
#include <GL/glew.h>
#include <thread>
#include "VFile.h"
class Texture2D
{
public:

	Texture2D(const char* path,bool alpha);
	Texture2D(const char* path, bool alpha, bool absPath);
	Texture2D(unsigned char* data, int w, int h,bool alpha = true);
	Texture2D(int w, int h);
	Texture2D(VFile* fil);
	~Texture2D();
	void Bind(int unit);
	void Release(int unit);
	int GetWidth();
	int GetID() {

		return (int)ID;

	};
	int GetHeight();
	void finish();
	const char* GetPath() {
		return texPath;
	}
	void LoadSub(char* buf);
	Texture2D(int w, int h, bool alpha);
	void Set(int w, int h, bool alpha,unsigned char * dat) {
		Width = w;
		Height = h;
		Raw = dat;
		Alpha = alpha;
		loaded = true;
	}

	void UntilLoaded();

	bool GetAlpha() {
		return Alpha;
	}

	unsigned char* GetRaw() {
		return Raw;
	}

	void SetLoaded(bool b) {

		loaded = b;

	}

	void Write(VFile* fil)
	{
		while (loaded == false) {

		}
		fil->WriteInt(Width);
		fil->WriteInt(Height);
		fil->WriteBool(Alpha);
		int bpp = 3;
		if (Alpha) {
			bpp = 4;
		}
		int ts = Width * Height * bpp;
		fil->WriteBytes((void*)Raw, ts);
	}


private:

	GLuint ID;
	unsigned char* Raw;
	int Width, Height;
	bool Alpha;
	std::thread thread;
	const char* texPath;
	bool loaded = false;
	bool binded = false;
	std::thread thr;
};

