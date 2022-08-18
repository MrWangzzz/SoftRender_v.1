#pragma once
struct Buffer
{
	int height, width;
};
struct DepthBuffer:Buffer
{
	DepthBuffer(int width, int height) 
	{
		this->height = height;
		this->width = width;
	}
};