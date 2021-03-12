#include "pch.h"
#include "NodeCam.h"
#include <glm/ext.hpp>

void NodeCam::SetViewport(int x, int y, int w, int h) {


	//mProj = glm::perspective<float>(65.0f, (float)w / (float)h, 0.1f, 1000.0f);
	mProj = glm::perspectiveFov(45.0f, (float)w, (float)h, 0.1f, 1000.0f);
}

glm::mat4 NodeCam::GetWorld() {

	glm::mat4 world = NodeBase::GetWorld();

	glm::mat ret = glm::inverse(world);

	return ret;

}