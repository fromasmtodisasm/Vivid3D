#include "pch.h"
#include "MapNode.h"

Texture2D* MapNode::Icon = NULL;
Texture2D* MapNode::Shadow = NULL;

MapNode::MapNode() {

	Pos = Vec3(0, 0, 1);

	if (Icon == NULL) {
		Icon = new Texture2D("edit/node1.png", true, false);
		Shadow = new Texture2D("game/shadow1.png", false, false);
	}
	Name = (const char*)malloc(512);
	char* nn = (char*)Name;
	nn[0] = "N"[0];
	nn[1] = "\0"[0];
	Image = Icon;
	Type = NodeType::TypeNode;


}


void MapNode::SetPos(float x, float y, float z) {


	Pos = Vec3(x, y, z);

}

void MapNode::SetPos(Vec3 p) {

	Pos = p;

	if (pBody != NULL) {

		//cpBodySetPosition(pBody, cpv(p.X, p.Y));

	}

}

Vec3 MapNode::GetPos() {

	return Pos;
}