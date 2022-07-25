#pragma once
#include"Vector3.h"
class Vertex
{
public :
	Vector3<float> pos;
	Vector3<float> normal;
	Vector2 uv;
	Vertex(const Vector3<float>& p, Vector2 uv);
	Vertex(const Vector3<float>& p, const Vector3<float>& normal, Vector2 uv);
	Vertex() {};
};

