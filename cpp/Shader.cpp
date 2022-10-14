#include"Shader.h"
void PhongShader::VertexShader(Vertex& v0, Vertex& v1, Vertex& v2)
{
	Vertex* v = &v0;
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			v = &v0;
			break;
		case 1:
			v = &v1;
			break;
		case 2:
			v = &v2;
			break;
		default:
			break;
		}
		v = v * v2f.m;
	}


}