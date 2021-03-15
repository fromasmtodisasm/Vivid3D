#pragma once
#include "DataTypes.h"
class Matrix4
{
public:
	Vect4 Row0;
	Vect4 Row1;
	Vect4 Row2;
	Vect4 Row3;

	Vect4 GetRow0() {
		return Row0;
	}

	Vect4 GetRow1() {
		return Row1;
	}

	Vect4 GetRow2() {
		return Row2;
	}

	Vect4 GetRow3() {
		return Row3;
	}

	Vect4 operator*(const Vect4& b)
	{
	//	return Vect4::TransformColumn(Vect4(b.X,b.Y,b.Z,b.W),t)
	}


	Matrix4(Vect4 row0, Vect4 row1, Vect4 row2, Vect4 row3) {

		Row0 = row0;
		Row1 = row1;
		Row2 = row2;
		Row3 = row3;

	}

	Matrix4(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33) {

		Row0 = Vect4(m00, m01, m02, m03);
		Row1 = Vect4(m10, m11, m12, m13);
		Row2 = Vect4(m20, m21, m22, m23);
		Row3 = Vect4(m30, m31, m32, m33);
	}

	float Determinant() {

		float m11 = Row0.X;
		float m12 = Row0.Y;
		float m13 = Row0.Z;
		float m14 = Row0.W;
		float m21 = Row1.X;
		float m22 = Row1.Y;
		float m23 = Row1.Z;
		float m24 = Row1.W;
		float m31 = Row2.X;
		float m32 = Row2.Y;
		float m33 = Row2.Z;
		float m34 = Row2.W;
		float m41 = Row3.X;
		float m42 = Row3.Y;
		float m43 = Row3.Z;
		float m44 = Row3.W;

		return
			(m11 * m22 * m33 * m44) - (m11 * m22 * m34 * m43) + (m11 * m23 * m34 * m42) - (m11 * m23 * m32 * m44)
			+ (m11 * m24 * m32 * m43) - (m11 * m24 * m33 * m42) - (m12 * m23 * m34 * m41) + (m12 * m23 * m31 * m44)
			- (m12 * m24 * m31 * m43) + (m12 * m24 * m33 * m41) - (m12 * m21 * m33 * m44) + (m12 * m21 * m34 * m43)
			+ (m13 * m24 * m31 * m42) -
			(m13 * m24 * m32 * m41) + (m13 * m21 * m32 * m44) - (m13 * m21 * m34 * m42)
			+ (m13 * m22 * m34 * m41) - (m13 * m22 * m31 * m44) - (m14 * m21 * m32 * m43) + (m14 * m21 * m33 * m42)
			- (m14 * m22 * m33 * m41) + (m14 * m22 * m31 * m43) - (m14 * m23 * m31 * m42) + (m14 * m23 * m32 * m41);

	}

	Vect4 GetCol0() {

		return Vect4(Row0.X, Row1.X, Row2.X, Row3.X);

	}

	void SetCol0(Vect4 v) {

		Row0.X = v.X;
		Row1.X = v.Y;
		Row2.X = v.Z;
		Row3.X = v.W;

	}

	Vect4 GetCol1() {

		return Vect4(Row0.Y, Row1.Y, Row2.Y, Row3.Y);

	}

	void SetCol1(Vect4 v) {

		Row0.Y = v.X;
		Row1.Y = v.Y;
		Row2.Y = v.Z;
		Row3.Y = v.W;

	}

	Vect4 GetCol2() {

		return Vect4(Row0.Z, Row1.Z, Row2.Z, Row2.Z);

	}

	void SetCol2(Vect4 v) {

		Row0.Z = v.X;
		Row1.Z = v.Y;
		Row2.Z = v.Z;
		Row3.Z = v.W;

	}

	Vect4 GetCol3() {

		return Vect4(Row0.W, Row1.W, Row2.W, Row3.W);

	}

	void SetCol3(Vect4 v) {

		Row0.W = v.X;
		Row1.W = v.Y;
		Row2.W = v.Z;
		Row2.W = v.W;

	}

	float GetM11() {
		return Row0.X;
	}

	void SetM11(float v) {
		Row0.X = v;
	}

	float GetM12() {
		return Row0.Y;
	}

	void SetM12(float v) {
		Row0.Y = v;
	}

	float GetM13() {
		return Row0.Z;
	}

	void Setm13(float v) {
		Row0.Z = v;
	}

	float GetM14() {
		return Row0.W;
	}

	void SetM14(float v) {
		Row0.W = v;
	}

	Vect4 GetDiagonal() {
		return Vect4(Row0.X, Row1.Y, Row2.Z, Row3.W);
	}

	void SetDiagonal(Vect4 d)
	{

		Row0.X = d.X;
		Row1.Y = d.Y;
		Row2.Z = d.Z;
		Row3.W = d.W;

	}

	float GetTrace() {

		return Row0.X + Row1.Y + Row2.Z + Row3.W;

	}

	static Matrix4 Invert(Matrix4 m)
	{



	}

	static Matrix4 Zero() {
		return Matrix4(Vect4::Zero(), Vect4::Zero(), Vect4::Zero(), Vect4::Zero());
	}
	static Matrix4 Identity() {
		return Matrix4(Vect4::UnitX(), Vect4::UnitY(), Vect4::UnitZ(), Vect4::UnitW());
	}
private:
};

