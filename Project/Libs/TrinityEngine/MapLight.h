#pragma once
#include "MapNode.h"
#include "Vec2.h"
#include "Application.h"
#include "kFrameBuffer.h"
class MapLight : public MapNode
{
public:
	MapLight(bool createShadowMap = true);

	void SetDiffuse(Vec3 diff);
	Vec3 GetDiffuse();
	bool HasSB() {
		if (shadowMap != NULL) {
			return true;
		}
		else {
			return false;
		}
	}
	float GetRange();
	Vec3* GetDiffusePtr() {

		return &Diff;

	}

	float* GetRangePtr() {

		return &Range;

	}

	float* GetSpotDirPtr() {

		return &SpotDir;
	}

	float* GetSpotAnglePtr() {

		return &SpotAngle;

	}

	bool* GetSpotPtr() {
		return &IsSpot;
	}

	void Turn(float a) {

		SpotDir += a;
		float v = SpotDir;
		if (v < 0) {
			v = 360.0f + v;
		}
		if (v > 360) {
			v = v - 360.0f;
		}
		SpotDir = v;

	}

	void SetRange(float range);

	void SetRender(float x, float y, float z, float r) {

		RPos = Vec3(x, y, z);
		RRange = r;

	}
	Vec3 GetRPos() {
		return RPos;
	}
	float GetRRange() {
		return RRange;
	}
	void Render();

	void SetSpot(bool spot) {
		IsSpot = spot;
	}

	void SetSpotAngle(float ang) {

		SpotAngle = ang;

	}

	bool GetSpot() {
		return IsSpot;
	}

	float GetSpotAngle() {
		return SpotAngle;
	}

	

	float GetSpotDir() {
		float v = SpotDir;

		if (v < 0) {
			v = 360.0f + v;
		}
		if (v > 360) {
			v = v - 360.0f;
		}
		return v;
		return SpotDir;
	}

	void SetSpotDir(float v) {
		if (v < 0) {
			v = 360.0f + v;
		}
		if (v > 360) {
			v = v - 360.0f;
		}
		SpotDir = v;

	}

	void BindSB() {

		shadowMap->bind();

	}
	
	void UnbindSB() {

		shadowMap->unbind();

	}

	kFrameBuffer* GetSB() {
		return shadowMap;
	}

	void SetBakedShadows(Texture2D* tex) {

		bakedShadows = tex;
	}

	Texture2D* GetBakedShadows() {

		return bakedShadows;

	}

	bool GetDynamic() {
		return dynamic;
	}

private:
	Vec3 RPos;
	float RRange;

	Vec3 Diff;
	Vec3 Spec;
	Vec3 Amb;
	float Range;
	bool IsSpot = false;
	float SpotDir = -90;
	float SpotAngle = 35.0f;
	kFrameBuffer* shadowMap;
	Texture2D* bakedShadows;
	bool dynamic = false;

};

