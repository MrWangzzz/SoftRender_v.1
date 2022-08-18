#pragma once
#include "Color.h"
#include <wtypes.h>
#include "Vertex.h"
#include"Mesh.h"
#include "Buffer.h"
class  Renderer
{

private:
	HDC screenHDC;
	int deviceWidth;
	int deviceHeight;


public:

	Renderer(HDC hdc, int screenWidth, int screenHeight);
	void DrawMesh(Mesh *mesh, DepthBuffer* zbuffer);
	void DrawTriangle(Vertex v1, Vertex v2, Vertex v3);
	void DrawLine(Vector3<float> p1, Vector3<float> p2);
private:
	
	void DrawPixel(int x, int y);
	void DrawTopFaltTrangle(Vertex v1, Vertex v2, Vertex v3);
	void DrawBottomFaltTrangle(Vertex v1, Vertex v2, Vertex v3);
	void DrawByIndex(Mesh *mesh, DepthBuffer* zbuffer);
	void DrawByArray(Mesh* mesh, DepthBuffer* zbuffer);
	void DrawPrimitive(Vertex v1, Vertex v2, Vertex v3, DepthBuffer* zbuffer);
	void PrepareRasterization(Vertex& vertex, Buffer* buffer);
};


