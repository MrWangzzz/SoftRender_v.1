#pragma once
#include <wtypes.h>
class Window
{
public :
	HWND window;
	int windowWidth;
	int windowHeight;
	HDC hdc;
	HDC screenHDC;

	Window(int w,int h,const char*name);
};

