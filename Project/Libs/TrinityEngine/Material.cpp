#include "pch.h"
#include "Material.h"

Material::Material() {

	ColorTex = NULL;
	NormalTex = NULL;
	SpecularTex = NULL;

}

void Material::SetColorTex(Texture2D* tex) {

	ColorTex = tex;

}

void Material::SetNormalTex(Texture2D* tex) {

	NormalTex = tex;

}

void Material::SetSpecularTex(Texture2D* tex) {

	SpecularTex = tex;

}

Texture2D* Material::GetColorTex() {

	return ColorTex;

}

Texture2D* Material::GetNormalTex() {

	return NormalTex;

}

Texture2D* Material::GetSpecularTex() {

	return SpecularTex;

}

void Material::Bind() {

	ColorTex->Bind(0);
	if (NormalTex != NULL) {
		NormalTex->Bind(1);
	}

}

void Material::Release() {

	ColorTex->Release(0);
	if (NormalTex != NULL) {
		NormalTex->Release(1);
	}

}