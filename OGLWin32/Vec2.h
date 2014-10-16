#pragma once

#include <math.h>

class Vec2
{
protected:
	float _x;
	float _y;
	void Copy(const Vec2& copied);
public:
	Vec2(float x, float y);
	Vec2();
	~Vec2();
	Vec2(const Vec2& copy);

	//Accessors Mutators
	const float X() const;
	void X(float x);
	const float Y() const;
	void Y(float y);

	Vec2& operator= (const Vec2& right);
	//Basic Operators.
	const Vec2 operator+(const Vec2& right) const;
	const Vec2 operator-(const Vec2& right) const;
	const Vec2 operator*(const Vec2& right) const;
	Vec2& operator+=(const Vec2& right);
	Vec2& operator-=(const Vec2& right);
	Vec2& operator*=(const Vec2& right);
	//Scalar
	const Vec2 operator*(float right) const;
	const Vec2 operator/(float right) const;
	//Bool
	const bool operator==(const Vec2& right);
	const bool operator!=(const Vec2& right);

	const float Modulus() const;
	const float DotProduct(const Vec2& right) const;
protected:

};
