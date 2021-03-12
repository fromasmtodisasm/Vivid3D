#pragma once
#include "DataTypes.h"
#include <vector>
#include "Material.h"
class Mesh3D
{
public:
	Mesh3D(int vertices, int tris) {

		Vertices.resize(vertices);
		Tris.resize(tris);

	}

	void SetVertex(int id, Vertex v) {

		Vertices[id] = v;

	}

	void SetTri(int id, Tri t) {

		Tris[id] = t;

	}

	Vertex GetVertex(int id) {
		
		return Vertices[id];
	
	}

	Tri GetTri(int id) {
	
		return Tris[id];
	
	}

	int NumVertices() {

		return (int)Vertices.size();


	}

	int NumTris() {

		return (int)Tris.size();
		
	}

	void CreateVBO();
	void BindVBO();
	void ReleaseVBO();
	void DrawVBO();
	void SetMaterial(Material* mat);
	Material* GetMaterial();

	void BindMaterial();
	void ReleaseMaterial();


private:
	
	std::vector<Vertex> Vertices;
	std::vector<Tri> Tris;
	GLuint VertexArray;
	GLuint VertexBuffer;
	Material* Mat;



};

