#pragma once

//I considered inheriting from Vector2D, but it's not worth it
//You have to rewrite all the classes and there's some memory
//And performance issues to consider if you were to cast
//Each 3D Vector into 2D just to perform operations on it.
//Not worth it, just for a Accessor/Mutator and Copy.

//A Vector3 is not a Vector2, It IS a VectorN but again, performance.
#include <math.h>
#include "Vec3.h"

class Vec3
{
protected:
	float _x;
	float _y;
	float _z;
	void Copy(const Vec3& copied);
public:
	Vec3(float x, float y, float z);
	Vec3();
	~Vec3();
	Vec3(const Vec3& copy);

	//Accessors Mutators
	const float X() const;
	void X(float x);
	const float Y() const;
	void Y(float y);
	const float Z() const;
	void Z(float z);

	Vec3& operator= (const Vec3& right);
	//Basic Operators.
	const Vec3 operator+(const Vec3& right) const;
	const Vec3 operator-(const Vec3& right) const;
	const Vec3 operator*(const Vec3& right) const;
	Vec3& operator+=(const Vec3& right);
	Vec3& operator-=(const Vec3& right);
	Vec3& operator*=(const Vec3& right);
	//Scalar
	const Vec3 operator*(float right) const;
	const Vec3 operator/(float right) const;
	//Bool
	const bool operator==(const Vec3& right);
	const bool operator!=(const Vec3& right);

	const float Modulus() const;
	const float DotProduct(const Vec3& right) const;
protected:

};
