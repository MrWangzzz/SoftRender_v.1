#pragma once
#include"Vector3.h"
#include"Matrix.h"
struct PhongVert
{
	//Vector3<float>
	//MVP����
	Matrix m, v, p;

	Vertex v0, v1, v2;
};
struct PhongFrag
{

};