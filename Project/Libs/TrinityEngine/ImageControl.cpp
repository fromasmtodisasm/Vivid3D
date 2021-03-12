#include "pch.h"
#include "ImageControl.h"
#include "Texture2D.h"
#include "UI.h"
ImageControl::ImageControl(Texture2D* image) {

	Image = image;

};


ImageControl::ImageControl(const char* path,bool alpha) {


	Image = new Texture2D(path, alpha);

};

void ImageControl::Render() {

	UI::DrawTexture(Image, GetX(), GetY(), GetW(), GetH(), 1, 1, 1, 1);

};