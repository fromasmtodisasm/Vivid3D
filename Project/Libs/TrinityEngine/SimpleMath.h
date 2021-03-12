#pragma once
#include "Vec2.h"
#include <math.h>

const float PI = 3.1415926535897932384626433;


inline float degToRad(float v) {

	return (v * PI) / 180.0f;

}

inline float radToDeg(float v) {

	return(v * 180.0f) / PI;

}

inline Vec2 vecAdd(Vec2 p, float x, float y) {

	return Vec2(p.X + x, p.Y + y);

}

inline float area(int x1, int y1, int x2, int y2, int x3, int y3)
{

	return abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

inline bool isInside(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y)
{
	/* Calculate area of triangle ABC */
	float A = area(x1, y1, x2, y2, x3, y3);

	/* Calculate area of triangle PBC */
	float A1 = area(x, y, x2, y2, x3, y3);

	/* Calculate area of triangle PAC */
	float A2 = area(x1, y1, x, y, x3, y3);

	/* Calculate area of triangle PAB */
	float A3 = area(x1, y1, x2, y2, x, y);

	/* Check if sum of A1, A2 and A3 is same as A */
	return (A == A1 + A2 + A3);
}


inline Vec2 rotatePoint(Vec2 p, float angle)
{
	angle = degToRad(angle);

	float s = sin(angle);
	float c = cos(angle);

	Vec2 np(p.X * c - p.Y * s,p.X * s + p.Y * c);

	return np;

}