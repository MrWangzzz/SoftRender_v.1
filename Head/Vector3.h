#pragma once

template<class T>
class  Vector3
{
public:
	 
	T x, y, z, w;
	Vector3<T>(T fx, T fy, T fz);
	Vector3<T>(T fx, T fy, T fz, T fw);
	Vector3() 
	{
		x = y = z = 0;
		w = 1;
	}
	Vector3<T> operator+(const Vector3<T>& right);
	Vector3<T> operator-(const Vector3<T>& right);
	Vector3<T> operator*(float value);
	Vector3<T> operator/(float value);

private:

};

template<class T>
inline Vector3<T>::Vector3(T fx, T fy, T fz)
{
	x = fx;
	y = fy;
	z = fz;
	w = 1;
}

template<class T>
inline Vector3<T>::Vector3(T fx, T fy, T fz, T fw)
{
	x = fx;
	y = fy;
	z = fz;
	w = fw;
}

template<class T>
inline Vector3<T> Vector3<T>::operator+(const Vector3<T>& right)
{
	Vector3<T> v3 = (x + right.x, y + right.y, z + right.z, w + right.w);
	return v3;
}

template<class T>
inline Vector3<T> Vector3<T>::operator-(const Vector3<T>& right)
{
	Vector3<T> v3 = (x - right.x, y - right.y, z - right.z, w - right.w);
	return v3;
}

template<class T>
inline Vector3<T> Vector3<T>::operator*(float value)
{
	Vector3 v3 = (x * value, y * value, z * value, z * value);
	return v3;
}

template<class T>
inline Vector3<T> Vector3<T>::operator/(float value)
{
	Vector3 v3 = (x / value, y / value, z / value, z / value);
	return v3;
}

class Vector2
{
public:
	float x, y;
	Vector2() { x = y = 0; }
	Vector2(float fx,float fy)
	{
		x = fx;
		y = fy;
	}

	Vector2 operator+(const Vector2& right);
	Vector2 operator-(const Vector2& right);
	Vector2 operator*(float value);
	Vector2 operator/(float value);
		  
private:

};


inline Vector2 Vector2::operator+(const Vector2& right)
{
	return Vector2(x + right.x, y + right.y);
}
inline Vector2 Vector2::operator-(const Vector2& right)
{
	return Vector2(x - right.x, y - right.y);
}
inline Vector2 Vector2::operator*(float value)
{
	return Vector2(x * value, y *value);
}
inline Vector2 Vector2::operator/(float value)
{
	return Vector2(x /value, y/value);
}