#ifndef UNICODE
#define UNICODE
#endif 
#include "Window.h"


LRESULT WINAPI MsgProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	Window* window = static_cast<Window*>(GetPropA(hwnd, "Owner"));

	if (!window)
		return DefWindowProcA(hwnd, Msg, wParam, lParam);

	switch (Msg)
	{
	}

	return DefWindowProcA(hwnd, Msg, wParam, lParam);
}

Window::Window(int w, int h, const char* name) :windowWidth(w), windowHeight(h)
{
	WNDCLASS wndC = { CS_BYTEALIGNCLIENT,(WNDPROC)MsgProc,0,0,0,NULL,NULL,NULL,NULL,TEXT("text") };
	wndC.hInstance = GetModuleHandle(NULL);

	if (!RegisterClass(&wndC))
	{
		return;
	}
	window = CreateWindow(TEXT("text"), TEXT("text"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, 0, 0, NULL, NULL, wndC.hInstance, NULL);
	if (window == NULL)
	{
		return;
	}
	hdc = GetDC(window);
	screenHDC = CreateCompatibleDC(hdc);

	BITMAPINFO bitmapInfo = { { sizeof(BITMAPINFOHEADER),windowWidth, windowHeight, 1, 32, BI_RGB, windowWidth * windowHeight * 4, 0, 0, 0, 0 } };
	LPVOID ptr;

	HBITMAP bitmapHandler = CreateDIBSection(screenHDC, &bitmapInfo, DIB_RGB_COLORS, &ptr, 0, 0);
	if (bitmapHandler == NULL)
		return;

	HBITMAP screenObject = (HBITMAP)SelectObject(screenHDC, bitmapHandler);

	SetWindowPos(window, NULL, 50, 50, windowWidth, windowHeight, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));

	ShowWindow(window, SW_NORMAL);
	UpdateWindow(window);


}
