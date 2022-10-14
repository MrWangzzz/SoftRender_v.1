#pragma once
#include"Vector3.h"
#include"Matrix.h"
class DirectionLight
{
public:
	/// <summary>
	/// π‚’’«ø∂»
	/// </summary>
	float intensity;

	DirectionLight() { intensity = 1; }
	DirectionLight(const Vector3<float>& dir, const Vector3<float>& pos, float Intensity = 1) 
	{
		direction = dir;
		position = pos;
		intensity = Intensity;
	}
	Vector3<float> GetDirection() 
	{
		return Vector3<float>(0, 0, 0) - direction;
	}
	//Matrix LookAt(const Vector3<float>& upAxis);

private:
	Vector3<float> direction;
	Vector3<float> position;

};

