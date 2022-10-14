#pragma once
#include"Vertex.h"
#include"Uniform.h"
struct BaseShader
{
public:
	virtual void VertexShader(Vertex& v0,Vertex& v1,Vertex&v2)=0;
	virtual void FragmentShader(Vertex& v, Vector3<float> g)=0;
};
struct PhongShader :public BaseShader
{
public:
	PhongShader(PhongVert v2f, PhongFrag frag) :v2f(v2f), frag(frag) {}
	virtual void VertexShader(Vertex& v0, Vertex& v1, Vertex& v2) override;
	virtual void FragmentShader(Vertex& v, Vector3<float> g) override;
public:
	PhongVert v2f;
	PhongFrag frag;
};