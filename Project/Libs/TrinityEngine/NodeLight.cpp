#include "pch.h"
#include "NodeLight.h"

NodeLight::NodeLight() {

	Diffuse = Vect3(1, 1, 1);
	Specular = Vect3(1, 1, 1);
	Range = 500;
	Shininess = 0.3f;

}

Vect3 NodeLight::GetDiffuse() {

	return Diffuse;

}

Vect3 NodeLight::GetSpecular() {

	return Specular;

}

float NodeLight::GetRange()
{
	return Range;
}

float NodeLight::GetShininess() {

	return Shininess;

}

void NodeLight::SetDiffuse(Vect3 diff) {

	Diffuse = diff;

}

void NodeLight::SetSpecular(Vect3 spec) {

	Specular = spec;

}

void NodeLight::SetRange(float range) {

	Range = range;

}

void NodeLight::SetShininess(float shine) {

	Shininess = shine;

}