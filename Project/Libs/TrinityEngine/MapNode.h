#pragma once
#include "Vec2.h"
#include "Texture2D.h"
#include <chipmunk.h>
//#include "Map.h"
#include "LScript.h"


class Map;

enum NodeType {
	TypeLight,TypeNode,Other
};

class MapNode
{
public:
	MapNode();
	void SetPos(float x, float y, float z = 1);
	void SetPos(Vec3 p);
	Vec3 GetPos();
	virtual void Render() {};
	virtual void MouseDown(int b) {};
	virtual void MouseUp(int b) {};
	virtual void MouseMove(int x, int y, int xd, int yd) {};

	void SetT(float* tx, float* ty) {

		TX = tx;
		TY = ty;

	}

	float* GetTX() {
		return TX;
	}

	float* GetTY() {
		return TY;
	}
	void SetIcon(Texture2D* icon) {
		Icon = icon;
	}
	Texture2D* GetIcon() {
		return Icon;
	}

	NodeType GetType() {
		return Type;
	}
	const char* GetName() {
		return Name;
	}
	void SetName(const char* name) {
		Name = name;
	}

	void AlignPhysics() {

		Vec3 p = GetPos();

		cpBodySetPosition(pBody, cpv(p.X, p.Y));

	}

	void CreateBoxPhysics(cpSpace * space,float sizeMod=1)
	{
		cpFloat mass = 1;

		// The moment of inertia is like mass for rotation
		// Use the cpMomentFor*() functions to help you approximate it.
		cpFloat moment = cpMomentForBox(mass, (float)(W)*sizeMod, (float)(H)*sizeMod);
		pBody = cpSpaceAddBody(space, cpBodyNew(mass, moment));
		cpBodySetPosition(pBody, cpv(Pos.X, Pos.Y));

		pShape = cpSpaceAddShape(space, cpBoxShapeNew(pBody, (float)(W)*sizeMod, (float)(H)*sizeMod, 0));
		cpShapeSetFriction(pShape, 0.02f);
		cpShapeSetElasticity(pShape, 0.1f);
	//	cpBodySetCenterOfGravity(pBody, cpv(W / 2, H / 2));
		physicsOn = true;
	

	}

	void GroundFriction(float fric) {

		cpVect cf = cpBodyGetVelocity(pBody);

		cf.x = cf.x * fric;
		cf.y = cf.y * fric;

		cpBodySetVelocity(pBody, cf);

	}

	virtual void Turn(float x) {

		Rot = Rot + x;

	}

	void SetBodyPos(Vec3 p) {

		cpBodySetPosition(pBody, cpv(p.X, p.Y));

	}

	void SetBodyAngle(float f) {

		cpBodySetAngle(pBody,f);
	}

	void ClearForces() {

		cpBodySetVelocity(pBody, cpv(0, 0));
		cpBodySetAngularVelocity(pBody, 0);

	}

	void AddForce(Vec3 f) {

		cpBodyApplyForceAtLocalPoint(pBody, cpv(f.X, f.Y), cpv(0, 0));

	}

	void SetVelocity(Vec3 f) {
		cpBodySetVelocity(pBody, cpv(f.X, f.Y));
	}

	bool GetPhysics() {

		return physicsOn;

	}
	float GetPhysicsRot() {

		float r = cpBodyGetAngle(pBody);



		//printf("P  ===== X:%f \n", r);

		//float r = cpBodyGetRotation(pBody).x;
		double degrees = (180 / 3.141592653589793238) * r;
		return degrees;

	}
	Vec3 GetPhysicsPos() {

		cpVect v = cpBodyGetPosition(pBody);

		Vec3 pos(v.x, v.y, 1.0f);

		return pos;

	}
	float GetRot() {
		return Rot;

	}
	void SetRot(float r) {
		Rot = r;
	}

	Texture2D* GetShadow() {

		return Shadow;

	}
	void SetData(void* data) {
		Data = data;
	}
	void* GetData() {
		return Data;
	}
	void SetLS(LScript* l) {

		LS = l;

	}
	LScript* GetLS() {

		return LS;

	}
	Texture2D* GetImage() {
		return Image;
	}

	void SetImage(Texture2D* img) {

		Image = img;

	}

	void SetSize(int w, int h) {

		W = w;
		H = h;

	}

	int GetW() {
		return W;
	}

	int GetH() {
		return H;
	}

	MapNode* Clone() {

		MapNode* nn = new MapNode;
		nn->SetName(GetName());
		nn->SetImage(GetImage());
		nn->SetSize(GetW(), GetH());
		nn->SetLS(GetLS());
		return nn;

	}

protected:
		
	Vec3 Pos;
	float* TX;
	float* TY;
	float W = 64;
	float H = 64;
	float Rot = 0;
	Texture2D* Image;
	
	static Texture2D* Icon;
	static Texture2D* Shadow;
	
	NodeType Type = NodeType::TypeNode;
	const char* Name = "Node0";
	cpBody *pBody;
	cpShape* pShape;
	bool physicsOn = false;
	void* Data;
	LScript* LS = NULL;

	
};

