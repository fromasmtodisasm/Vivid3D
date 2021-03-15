#include "pch.h"
#include "FXMeshFlat.h"

FXMeshFlat::FXMeshFlat() {

	load("Shader/3D/MeshFlatVert.glsl", "Shader/3D/MeshFlatFrag.glsl");

}

void FXMeshFlat::setPars() {

	setMat("mProj", mProj);
	setMat("mModel", mModel);
	setMat("mView", mView);
	setVec3("mCol", fCol.X, fCol.Y, fCol.Z);


}