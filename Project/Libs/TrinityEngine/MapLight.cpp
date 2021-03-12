#include "pch.h"
#include "MapLight.h"


MapLight::MapLight(bool createShadowMap) {

	Pos = Vec3(0, 0, 1);
	Diff = Vec3(1, 1, 1);
	Spec = Vec3(0.2f, 0.2f, 0.2f);
	Amb = Vec3(0.2f, 0.2f, 0.2f);
	Range = 350;
	Type = NodeType::TypeLight;

	if (createShadowMap) {
		shadowMap = new kFrameBuffer(Application::WinW, Application::WinH);
	}

}

void MapLight::Render() {



}

void MapLight::SetDiffuse(Vec3 diff) {

	Diff = diff;

}

void MapLight::SetRange(float range) {

	Range = range;

}

Vec3 MapLight::GetDiffuse() {

	return Diff;

}

float MapLight::GetRange() {

	return Range;

}