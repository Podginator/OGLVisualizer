#ifndef VEC_C_GUARD
#define VEC_C_GUARD



#include "Vec2.h"

Vec2::Vec2(float x, float y)
{
	_x = x;
	_y = y;
}

Vec2::Vec2()
{
	_x = 0.0f;
	_y = 0.0f;
}

Vec2::Vec2(const Vec2& copy)
{
	Copy(copy);

}

Vec2::~Vec2(){}

const float Vec2::X() const
{
	return _x;
}

void Vec2::X(float x)
{
	_x = x;
}

const float Vec2::Y() const
{
	return _y;

}

void Vec2::Y(float y)
{
	_y = y;
}

Vec2& Vec2::operator=(const Vec2& right)
{
	if (&right != this)
	{
		Copy(right);
	}

	return *this;
}

const Vec2 Vec2::operator+(const Vec2& right) const
{
	return Vec2(_x + right._x, _y + right._y);
}

const Vec2 Vec2::operator-(const Vec2& right) const
{
	return Vec2(_x - right._x, _y - right._y);
}

const Vec2 Vec2::operator*(const Vec2& right) const
{
	return Vec2(_x * right._x, _y * right._y);
}

Vec2& Vec2::operator+=(const Vec2& right)
{
	_x += right._x;
	_y += right._y;

	return *this;
}

Vec2& Vec2::operator-=(const Vec2& right)
{
	_x -= right._x;
	_y -= right._y;

	return *this;
}

const bool Vec2::operator==(const Vec2& right)
{
	return (_x == right._x && _y == right._y);
}

const  bool Vec2::operator!=(const Vec2& right)
{
	return (_x != right._x && _y != right._y);
}


Vec2& Vec2::operator*=(const Vec2& right)
{
	_x *= right._x;
	_y *= right._y;

	return *this;
}

const Vec2 Vec2::operator*(float right) const
{
	return Vec2(right*_x, right*_y);
}

const Vec2 Vec2::operator/(float right) const
{
	return Vec2(right / _x, right / _y);
}

const float Vec2::Modulus() const
{
	return sqrt(_x*_x + _y*_y);
}

const float Vec2::DotProduct(const Vec2& right) const
{
	return _x * right._x + _y + right._y;
}

void Vec2::Copy(const Vec2& copy)
{
	_x = copy._x;
	_y = copy._y;
}

#endif