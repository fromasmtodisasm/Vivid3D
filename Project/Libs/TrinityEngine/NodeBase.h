#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "DataTypes.h"
class NodeBase
{
public:

	NodeBase();
	Vect3 GetPosition();
	Vect3 GetScale();
	float GetPositionX();
	float GetPositionY();
	float GetPositionZ();
	void SetPosition(Vect3 pos);
	void SetPosition(float x, float y, float z);
	void LookAt(Vect3 p);
	void LookAt(float x, float y, float z);
	void SetScale(Vect3 scale);
	void Rotate(float p, float y, float r);
	void Turn(float p, float y, float r);
	void Move(float x, float y, float z);
	virtual glm::mat4 GetWorld();
	void Add(NodeBase* node);
	NodeBase* GetSub(int id);
	int NumSub();
	std::vector<NodeBase*> GetSub();
	void SetRoot(NodeBase* node);
	NodeBase* GetRoot();
	const char* GetName() {
		return Name;
	}
	void SetName(const char* name) {
		Name = name;
	}
private:
	glm::mat4 LocalTurn;
	glm::vec3 LocalScale;
	glm::vec3 LocalPos;

	std::vector<NodeBase*> Sub;

	NodeBase* Root = NULL;
	const char* Name = "";

};

