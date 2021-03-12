#pragma once
#include <glm/glm.hpp>

struct Vect3 {
	float X, Y, Z;

	Vect3(float x, float y, float z) {
		X = x;
		Y = y;
		Z = z;
	}
	Vect3() {
		X = Y = Z = 0;
	}
	Vect3(const Vect3& v) {
		X = v.X;
		Y = v.Y;
		Z = v.Z;
	}
	Vect3(glm::vec3 v) {
		X = v.x;
		Y = v.y;
		Z = v.z;
	}
};

struct Vect4 {
	float X, Y, Z, W;
	Vect4(float x, float y, float z, float w) {
		X = x;
		Y = y;
		Z = z;
		W = w;
	}
	Vect4() {
		X = Y = Z = W = 0;
	}
	Vect4(const Vect4& v) {
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		W = v.W;
	}
};

struct Vertex {

	Vect3 Pos;
	Vect4 Col;
	Vect3 UV;
	Vect3 Norm;
	Vect3 BiNorm;
	Vect3 Tan;
	Vertex() {

		Pos = Vect3();
		UV = Vect3();
		Col = Vect4();
		Norm = Vect3();
		BiNorm = Vect3();
		Tan = Vect3();

	}
	Vertex(Vect3 p, Vect3 uv, Vect4 col, Vect3 norm, Vect3 biNorm, Vect3 tan) {
		Pos = p;
		UV = uv;
		Col = col;
		Norm = norm;
		BiNorm = biNorm;
		Tan = tan;
	}

};

struct Tri {

	int V0, V1, V2;

	Tri(int v0, int v1, int v2) {
		V0 = v0;
		V1 = v1;
		V2 = v2;
	}

	Tri() {
		V0 = V1 = V2 = 0;
	}

	Tri(const Tri& t) {
		V0 = t.V0;
		V1 = t.V1;
		V2 = t.V2;
	}

};


