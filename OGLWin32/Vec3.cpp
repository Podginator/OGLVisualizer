#pragma once

#include "Vec3.h"

Vec3::Vec3(float x, float y,float z)
{
	_x = x;
	_y = y;
	_z = z;
}

Vec3::Vec3()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
}

Vec3::Vec3(const Vec3& copy)
{
	Copy(copy);
}

Vec3::~Vec3(){}

const float Vec3::X() const
{
	return _x;
}

void Vec3::X(float x)
{
	_x = x;
}

const float Vec3::Y() const
{
	return _y;

}

void Vec3::Y(float y)
{
	_y = y;
}

const float Vec3::Z() const
{
	return _z;

}

void Vec3::Z(float z)
{
	_z = z;
}

Vec3& Vec3::operator=(const Vec3& right)
{
	if (&right != this)
	{
		Copy(right);
	}

	return *this;
}

const Vec3 Vec3::operator+(const Vec3& right) const
{
	return Vec3(_x + right._x, _y + right._y, _z+right._z);
}

const Vec3 Vec3::operator-(const Vec3& right) const
{
	return Vec3(_x - right._x, _y - right._y, _z - right._z);
}

const Vec3 Vec3::operator*(const Vec3& right) const
{
	return Vec3(_x * right._x, _y * right._y, _z * right._z);
}

Vec3& Vec3::operator+=(const Vec3& right)
{
	_x += right._x;
	_y += right._y;
	_z += right._z;

	return *this;
}

Vec3& Vec3::operator-=(const Vec3& right)
{
	_x -= right._x;
	_y -= right._y;
	_z -= right._z;

	return *this;
}

const bool Vec3::operator==(const Vec3& right)
{
	return (_x == right._x && _y == right._y && _z == right._z);
}

const bool Vec3::operator!=(const Vec3& right)
{
	return !(*this == right);
}


Vec3& Vec3::operator*=(const Vec3& right)
{
	_x *= right._x;
	_y *= right._y;

	return *this;
}

const Vec3 Vec3::operator*(float right) const
{
	return Vec3(right*_x, right*_y, right*_z);
}

const Vec3 Vec3::operator/(float right) const
{
	return Vec3(right / _x, right / _y, right / _z);
}

const float Vec3::Modulus() const
{
	return sqrt(_x*_x + _y*_y + _z*_z);
}

const Vec3 Vec3::CrossProduct(const Vec3& right) const
{
	//Later.
	return Vec3(0, 0, 0);
}

void Vec3::Copy(const Vec3& copy)
{
	_x = copy._x;
	_y = copy._y;
	_z = copy._z;
}
