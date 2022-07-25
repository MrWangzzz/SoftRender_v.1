#include "Renderer.h"
#include <iostream>
using namespace std;



Renderer::Renderer(HDC hdc, int screenWidth, int screenHeight)
{
	screenHDC = hdc;
	deviceWidth = screenWidth;
	deviceHeight = screenHeight;
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

		///(v2.x-v1.x)/(v2.y-v1.y)
		///()

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
	int dx, dy, k, epsl;

	float x, y, xIncre, yIncre;


	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	x = p1.x;
	y = p1.y;
	if (dx==0)
	{
		DrawPixel(int(p1.x), (int)(p1.y));
		return;
	}
	epsl = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

	xIncre = (float)(dx / epsl);
	yIncre = (float)(dy / epsl);

	for (k = 0; k < epsl; k++)
	{
		DrawPixel(int(x), (int)(y));
		x += xIncre;
		y += yIncre;
	}


}

void Renderer::DrawPixel(int x, int y)
{
	SetPixel(screenHDC, x, y, RGB(0, 0, 0));
}