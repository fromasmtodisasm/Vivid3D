#pragma once
class Vec2
{
public:
	Vec2(float x, float y) {
		X = x;
		Y = y;
	}
	Vec2() {
		X = 0;
		Y = 0;
	}

	float X=0, Y=0;
};

class Vec3 {
public:
	Vec3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	Vec3()
	{
		X = Y = Z = 0;
	}

	float X, Y, Z;

};
