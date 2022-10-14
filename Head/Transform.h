#pragma once
#include"Vector3.h"
#include"Matrix.h"
#include "MyMath.h"
class Transform
{
public:
	Vector3<float> position;
	Vector3<float> rotation;
	Vector3<float> scale;

	Matrix Translate(const Vector3<float>& v);
	Matrix Scale(const Vector3<float>& s);

	Matrix Rotate(const Vector3<float>& rotAngle);
	//Matrix objectToWorld;
	//Matrix Translate(const Vector3<float>& v);
	Transform(Vector3<float> pos, Vector3<float> rot, Vector3<float> scale) :position(pos) , rotation(rot), scale(scale) {}
	Transform() { }
private:
	Matrix RotateX(float angle);
	Matrix RotateY(float angle);
	Matrix RotateZ(float angle);
};

