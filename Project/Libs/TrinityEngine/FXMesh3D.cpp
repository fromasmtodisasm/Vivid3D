#include "pch.h"
#include "FXMesh3D.h"

FXMesh3D::FXMesh3D() {

	load("Shader/3D/MeshVert.glsl", "Shader/3D/MeshFrag.glsl");
	//while (true) {


	//}

}

void FXMesh3D::setPars() {

	setMat("mProj", mProj);
	setMat("mModel", mModel);
	setMat("mView", mView);
	setInt("tCol", 0);
	setInt("tNorm", 1);

	auto pos = Light->GetPosition();
	auto diff = Light->GetDiffuse();
	auto spec = Light->GetSpecular();
	auto range = Light->GetRange();

	auto vpos = Cam->GetPosition();

	setVec3("lPos", pos.X, pos.Y, -pos.Z);
	setVec3("lDiff", diff.X, diff.Y, diff.Z);
	setVec3("lSpec", spec.X, spec.Y, spec.Z);
	setFloat("lRange", range);
	setVec3("viewPos", vpos.X, vpos.Y, vpos.Z);



}