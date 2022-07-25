#include "Window.h"
#include "Renderer.h"

Renderer* rd;

const int WindowWidth = 500;
const int WindowHeight = 500;

void Update(Window* w);
void DoRender(Window* w);
int main() 
{
	Window* w = new Window(WindowWidth, WindowHeight, "Test");

	rd = new Renderer(w->hdc, WindowWidth, WindowHeight);

	Update(w);
}
void Update(Window* w)
{

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		//UpdateInput(currentMesh);

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DoRender(w);
			//ShowFPS(w);
		}
	}
}
/// <summary>
/// »æÖÆ
/// </summary>
/// <param name="w"></param>
void DoRender(Window* w) 
{
	Vertex v1;
	v1.pos = Vector3<float>(150, 100, 0);

	Vertex v2;
	v2.pos = Vector3<float>(200, 200, 0);

	Vertex v3;
	v3.pos = Vector3<float>(100, 150, 0);
	//175 150


	rd->DrawTriangle(v1,v2,v3);
	//rd->DrawPixel(250,250);
}