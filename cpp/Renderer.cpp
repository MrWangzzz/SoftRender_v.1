#include "Renderer.h"
#include <iostream>
using namespace std;



Renderer::Renderer(HDC hdc, int screenWidth, int screenHeight,Camera *cam)
{
	screenHDC = hdc;
	deviceWidth = screenWidth;
	deviceHeight = screenHeight;
	camera = cam;
}



void Renderer::DrawMesh(Mesh* mesh, DepthBuffer* zbuffer)
{
	if (mesh->indexBuffer.size() > 0)
	{
		DrawByIndex(mesh, zbuffer);
	}
	else
	{
		DrawByArray(mesh, zbuffer);
	}
}


/// <summary>
/// 根据索引信息绘制
/// </summary>
/// <param name="mesh"></param>
void Renderer::DrawByIndex(Mesh* mesh, DepthBuffer* zbuffer)
{

	for (int i = 0; i < mesh->indexBuffer.size(); i = i + 4)
	{
		Vertex p1;
		p1.pos = mesh->positionBuffer[mesh->indexBuffer[i].x - 1];
		p1.uv = mesh->uvBuffer[mesh->indexBuffer[i].y - 1];
		p1.normal = mesh->normalBuffer[mesh->indexBuffer[i].z - 1];

		Vertex p2;
		p2.pos = mesh->positionBuffer[mesh->indexBuffer[i + 1].x - 1];
		p2.uv = mesh->uvBuffer[mesh->indexBuffer[i + 1].y - 1];
		p2.normal = mesh->normalBuffer[mesh->indexBuffer[i + 1].z - 1];

		Vertex p3;
		p3.pos = mesh->positionBuffer[mesh->indexBuffer[i + 2].x - 1];
		p3.uv = mesh->uvBuffer[mesh->indexBuffer[i + 2].y - 1];
		p3.normal = mesh->normalBuffer[mesh->indexBuffer[i + 2].z - 1];

		Vertex p4;
		p4.pos = mesh->positionBuffer[mesh->indexBuffer[i + 3].x - 1];
		p4.uv = mesh->uvBuffer[mesh->indexBuffer[i + 3].y - 1];
		p4.normal = mesh->normalBuffer[mesh->indexBuffer[i + 3].z - 1];

		DrawPrimitive(p1, p2, p3, zbuffer);
		DrawPrimitive(p1, p3, p4, zbuffer);
	}
}
/// <summary>
/// 绘制所以顶点
/// </summary>
/// <param name="mesh"></param>
void Renderer::DrawByArray(Mesh* mesh, DepthBuffer* zbuffer)
{
	for (int i = 0; i < mesh->vertexBuffer.size(); i = i + 3)
	{
		Vertex p1 = mesh->vertexBuffer[i];
		Vertex p2 = mesh->vertexBuffer[i + 1];
		Vertex p3 = mesh->vertexBuffer[i + 2];
		DrawPrimitive(p1, p2, p3, zbuffer);
	}
}

void Renderer::DrawPrimitive(Vertex v1, Vertex v2, Vertex v3, DepthBuffer* zbuffer)
{

	PrepareRasterization(v1, zbuffer);
	PrepareRasterization(v2, zbuffer);
	PrepareRasterization(v3, zbuffer);

	DrawTriangle(v1, v2, v3);
}
inline void Renderer::PrepareRasterization(Vertex& vertex, Buffer* buffer)
{
	float reciprocalW = 1.0f / vertex.pos.w;
	//最后加0.5是为了后面取证做四舍五入
	vertex.pos.x = vertex.pos.x * reciprocalW * buffer->width * 0.5f;
	vertex.pos.y = vertex.pos.y * reciprocalW * buffer->height * 0.5f;
}

void Renderer::DrawTriangle(Vertex v1, Vertex v2, Vertex v3)
{

	int y1 = v1.pos.y;
	int y2 = v2.pos.y;
	int y3 = v3.pos.y;

	if (y1 == y2)
	{
		//上平
		DrawTopFaltTrangle(v1, v2, v3);
	}
	else if (y2 == y3)
	{
		DrawBottomFaltTrangle(v1, v2, v3);
	}
	else
	{
		float x = (v2.pos.x - v1.pos.x) * (v3.pos.y - v1.pos.y) / (v2.pos.y - v1.pos.y) + v1.pos.x;
		float y = v3.pos.y;
		Vertex xv2(Vector3<float>(x, y, 0), Vector2(0, 0));

		DrawTopFaltTrangle(v3, xv2, v2);
		DrawBottomFaltTrangle(v1, xv2, v3);
	}

}






/// <summary>
/// 绘制上平三角形
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <param name="v3"></param>
void Renderer::DrawTopFaltTrangle(Vertex v1, Vertex v2, Vertex v3)
{
	float x1 = v1.pos.x;
	float y1 = v1.pos.y;

	float x2 = v2.pos.x;
	float y2 = v2.pos.y;

	float x3 = v3.pos.x;
	float y3 = v3.pos.y;


	for (float y = y1; y < y3; y++)
	{
		int xl = (y - y1) * (x3 - x1) / (y3 - y1) + x1;

		Vector3<float> vl(xl, y, 0);
		int xr = (y - y2) * (x3 - x2) / (y3 - y2) + x2;
		Vector3<float> vr(xr, y, 0);


		DrawLine(vl, vr);
	}
}
/// <summary>
/// 绘制下平三角形
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <param name="v3"></param>
/// <param name="Drawtype"></param>

void Renderer::DrawBottomFaltTrangle(Vertex v1, Vertex v2, Vertex v3)
{
	float x1 = v1.pos.x;
	float y1 = v1.pos.y;

	float x2 = v2.pos.x;
	float y2 = v2.pos.y;

	float x3 = v3.pos.x;
	float y3 = v3.pos.y;

	for (int y = y1; y < y3; y++)
	{
		int xl = (x3 - x1) * (y - y1) / (y3 - y1) + x1;
		Vector3<float> vl(xl, y, 0);
		int xr = (x2 - x1) * (y - y1) / (y2 - y1) + x1;
		Vector3<float> vr(xr, y, 0);

		DrawLine(vl, vr);
	}
}






/// <summary>
///DDA画线
/// </summary>
/// <param name="x0"></param>
/// <param name="y0"></param>
/// <param name="x1"></param>
/// <param name="y1"></param>
void Renderer::DrawLine(Vector3<float> p1, Vector3<float> p2)
{
	float dx, dy, k, epsl;

	float x, y, xIncre, yIncre;


	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	x = p1.x;
	y = p1.y;
	if (dx == 0)
	{
		DrawPixel(int(p1.x), (int)(p1.y));
		return;
	}
	epsl = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	xIncre = (dx / epsl);
	yIncre = (dy / epsl);

	for (k = 0; k < epsl; k++)
	{
		DrawPixel(int(x), (int)(y));
		x += xIncre;
		y += yIncre;
	}


}

void Renderer::DrawPixel(int x, int y)
{
	SetPixel(screenHDC, x, y, RGB(255, 255, 0));
}