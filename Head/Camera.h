#pragma once
#include "Transform.h"
class  Camera
{
public:
	Transform transform;
	//Matrix v, p;

	Camera(Transform t) : transform(t) {}
	Camera(){}

};

