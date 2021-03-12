#pragma once
#include "VFile.h"
#include "VString.h"
#include "Texture2D.h"
#include <vector>
class SpriteAnim
{
public:
	SpriteAnim(VString name)
	{
		Name = name;
		W = H = 0;
		CurrentFrame = 0;
		frames.resize(0);
	}
	void AddFrame(Texture2D* tex) {

		frames.push_back(tex);
		W = tex->GetWidth();
		H = tex->GetHeight();
		FrameCount++;

	}
	void LoadData(const char* path) {

		VFile f(path,FileMode::Read);

		int w;
		int h;

		w = f.ReadInt();
		h = f.ReadInt();

		W = w;
		H = h;

		int fc = f.ReadInt();

		FrameCount = fc;

		for (int i = 0; i < fc; i++) {

			void* dat = f.ReadBytes(w * h * 4);

			Texture2D* ntex = new Texture2D((unsigned char*)dat, w, h);

			frames.push_back(ntex);

			printf("Loaded Frame:%d\n", i);

		}

		f.Close();

	}

	Texture2D* GetFrame() {

		return frames[CurrentFrame];

	}

	void SetSpeed(float spd) {
		Speed = spd;
	}

	float GetSpeed() {
		return Speed;
	}

	VString GetName() {
		return Name;
	}

	void Play() {
		Playing = true;
		CurrentFrame = 0;
	}

	void Update() {
		Time += Speed;
		int ct = (int)Time;
		if (ct > CurrentFrame) {
			CurrentFrame = ct;
			if (CurrentFrame >= FrameCount) {
				CurrentFrame = 0;
				Time = 0;
			}
		}
	}

private:
	VString Name;
	int W, H;
	int CurrentFrame = 0;
	int FrameCount = 0;
	float Time = 0.0f;
	bool Playing = false;
	std::vector<Texture2D*> frames;
	float Speed = 0.4f;
};


