#pragma once
#include "NodeBase.h"
class NodeCam : public NodeBase
{
public:

	void SetViewport(int x, int y, int w, int h);
	glm::mat4 GetProj() {
		return mProj;
	}
	
	glm::mat4 GetWorld();

private:
	glm::mat4 mProj;
};

