#pragma once
#include"Transform.h"
#include<vector>
#include "Vertex.h"
class  Mesh
{
public:
	Transform transform;
	std::vector<Vertex> vertexBuffer;
	std::vector<Vector3<float>> positionBuffer;
	std::vector<Vector3<float>> normalBuffer;
	std::vector<Vector2> uvBuffer;
	std::vector<Vector3<int>> indexBuffer;
	Mesh();
	Transform GetTransform() { return transform; }


private:

};

