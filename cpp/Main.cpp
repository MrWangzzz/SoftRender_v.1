#include "Window.h"
#include "Renderer.h"
#include "ObjFileReader.h"
#include"Camera.h"
#include"Transform.h"
#include"Input.h"

Renderer* rd;
const int WindowWidth = 500;
const int WindowHeight = 500;
Vector3<float> moveVector, rotateVector;
Mesh* cube = new Mesh();

DepthBuffer *depthbuffer=new DepthBuffer(WindowWidth*2, WindowHeight*2);
Camera* camera = new Camera(Transform(Vector3<float>(0, 0, 100), Vector3<float>(0, 0, 0), Vector3<float>(0, 0, 0)));



void Update(Window* w);
void DoRender(Window* w);
void UpdateInput(Mesh* m);
int main() 
{
	Window* w= new Window(WindowWidth, WindowHeight, "Test");
	rd = new Renderer(w->screenHDC, WindowWidth, WindowHeight, camera);
	ReadObjFile("cube.obj", cube);
	Update(w);
}
void Update(Window* w)
{

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		UpdateInput(cube);

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
	rd->DrawMesh(cube, depthbuffer);
	BitBlt(w->hdc, 0, 0, WindowWidth, WindowHeight, w->screenHDC, 0, 0, SRCCOPY);
}
Matrix M;
void UpdateInput(Mesh* m)
{
	if (IS_KEY_DOWN('A'))
	{
		moveVector.x -= 0.01f;
	}
	if (IS_KEY_DOWN('D'))
	{
		moveVector.x += 0.01f;
	}
	if (IS_KEY_DOWN('W'))
	{
		moveVector.y += 0.01f;
	}
	if (IS_KEY_DOWN('S'))
	{
		moveVector.y -= 0.01f;
	}
	if (IS_KEY_DOWN('E'))
	{
		moveVector.z -= 0.1f;
	}
	if (IS_KEY_DOWN('Q'))
	{
		moveVector.z += 0.1f;
	}
	if (IS_KEY_DOWN('I'))
	{
		rotateVector.y += 0.1f;
	}
	if (IS_KEY_DOWN('K'))
	{
		rotateVector.y -= 0.1f;
	}
	if (IS_KEY_DOWN('L'))
	{
		rotateVector.x += 0.5f;
	}
	if (IS_KEY_DOWN('J'))
	{
		rotateVector.x -= 0.5f;
	}
	if (IS_KEY_DOWN('U'))
	{
		rotateVector.z -= 0.1f;
	}
	if (IS_KEY_DOWN('O'))
	{
		rotateVector.z += 0.1f;
	}
	Transform mtrs = m->GetTransform();

	Matrix s = mtrs.Scale(Vector3<float>(1, 1, 1));
	Matrix r = mtrs.Rotate(rotateVector);
	Matrix t = mtrs.Translate(moveVector);
	M = t * r * s;
}
