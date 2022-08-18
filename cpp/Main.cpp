#include "Window.h"
#include <Renderer.h>
#include "ObjFileReader.h"

Renderer* rd;

const int WindowWidth = 500;
const int WindowHeight = 500;

Mesh* m = new Mesh();
void Update(Window* w);
void DoRender(Window* w);
void UpdateInput(Mesh* m);
int main() 
{
	Window* w= new Window(WindowWidth, WindowHeight, "Test");
	rd = new Renderer(w->screenHDC, WindowWidth, WindowHeight);
	ReadObjFile("cube.obj", m);
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
	rd->DrawMesh(m);
	BitBlt(w->hdc, 0, 0, WindowWidth, WindowHeight, w->screenHDC, 0, 0, SRCCOPY);
}
void UpdateInput(Mesh* m)
{

}
