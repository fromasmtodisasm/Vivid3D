#include "ImageDropControl.h"
void ImageDropControl::Drop(UIControl* drop) {

	printf("Dropping:");
	printf(drop->GetText());
	printf("|\n");
	
	Image =(Texture2D*) drop->GetData();

}

ImageDropControl::ImageDropControl(Texture2D* tex) {

	Image = tex;
 
}