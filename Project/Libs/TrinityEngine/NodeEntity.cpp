#include "pch.h"
#include "NodeEntity.h"

NodeEntity::NodeEntity() {


}

void NodeEntity::AddMesh(Mesh3D* mesh) {

	Meshes.push_back(mesh);

}

int NodeEntity::NumMeshes() {

	return Meshes.size();

}

Mesh3D* NodeEntity::GetMesh(int id) {

	return Meshes[id];

}

void NodeEntity::Render() {

	for (int i = 0; i < Meshes.size(); i++) {

		Meshes[i]->BindMaterial();
		Meshes[i]->BindVBO();
		Meshes[i]->DrawVBO();
		Meshes[i]->ReleaseVBO();
		Meshes[i]->ReleaseMaterial();

	}

}