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
		depthBuffer = new float* [height];

		for (int i = 0; i < height; i++) 
		{
			depthBuffer[i] = new float[width];
		}
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j< width; j++)
			{
				depthBuffer[i][j] = 1;
			}
		}
	}

	float clamp(float min,float max,float value)
	{
		if (value>max)
		{
			value = max;
		}
		if (value<min)
		{
			value = min;
		}
		return value;
	}
	float sample(float u, float v) 
	{
		int y = clamp(0, height - 1, u);
		int x = clamp(0, width - 1, v);
		return depthBuffer[y][x];
	}
	~DepthBuffer() 
	{
		for (int i = 0; i < height; i++)
		{
			delete[] depthBuffer[i];
		}
	}

	float **depthBuffer;

};