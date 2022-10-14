#include"Transform.h"

Matrix Transform::Translate(const Vector3<float>& v)
{
	position = v;
	Matrix m;
	m.Identity();
	m.value[0][3] = v.x;
	m.value[1][3] = v.y;
	m.value[2][3] = v.z;
	return m;
}

Matrix Transform::Scale(const Vector3<float>& s)
{
	Matrix m;
	scale = s;
	m.Identity();
	m.value[0][0] = s.x;
	m.value[1][1] = s.y;
	m.value[2][2] = s.z;
	return m;
}

Matrix Transform::Rotate(const Vector3<float>& rotAngle)
{
	rotation = rotAngle;
	Matrix rotx = RotateX(rotAngle.x);
	Matrix roty = RotateX(rotAngle.y);
	Matrix rotz = RotateX(rotAngle.z);
	return rotx * roty * rotz;
}

Matrix Transform::RotateX(float angle)
{
	rotation.x = angle;
	Matrix m;
	m.Identity();
	float radian = angle / 360.0f * PI;
	float cosvalue = cos(radian);
	float sinvalue = sin(radian);
	m.value[1][1] = cosvalue;
	m.value[1][2] = -sinvalue;
	m.value[2][1] = sinvalue;
	m.value[2][2] = cosvalue;
	return m;
		
}

Matrix Transform::RotateY(float angle)
{
	rotation.y = angle;
	Matrix m;
	m.Identity();
	float radian = angle / 360.0f * PI;
	float cosValue = cos(angle);
	float sinValue = sin(angle);
	m.value[0][0] = cosValue;
	m.value[0][2] = sinValue;
	m.value[2][0] = -sinValue;
	m.value[2][2] = cosValue;
	return m;
}

Matrix Transform::RotateZ(float angle)
{
	rotation.z = angle;
	Matrix m;
	m.Identity();
	float radian = angle / 360.0f * PI;
	float cosValue = cos(angle);
	float sinValue = sin(angle);
	m.value[0][0] = cosValue;
	m.value[0][1] = -sinValue;
	m.value[1][0] = sinValue;
	m.value[1][1] = cosValue;
	return m;
}
