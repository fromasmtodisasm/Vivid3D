#include "pch.h"
#include "MapSprite.h"


void MapSprite::Compile() {

	CompiledMesh = new Mesh2D();

	int w = SprWidth;
	int h = SprHeight;

	CompiledMesh->AddQuad(-w / 2, -h / 2, w, h, Anims[0]->GetFrame(), NULL, 1, 1, 1, 1);
	printf("W:%d H:%d\n", w, w);
	
	CompiledMesh->Compile();

}