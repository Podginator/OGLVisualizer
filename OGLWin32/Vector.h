#pragma once

#include <math.h>
#include <array>

template<size_t size, typename T>
class Vector
{
private:
	std::array<T, size> data;
	void Copy(const Vector& copied);
public:

	template<typename... Args>
	Vector(Args const&&... args) : data({ args... })
	{
	}

	Vector();
	Vector(const Vector& copy){ Copy(copy); }

	T& operator [](std::size_t const& index){return data[index];}
	const T& operator [](std::size_t const& index) const { return data[index]; }

	Vector& operator= (const Vector& right) { Copy(copy) };
	//Basic Operators.
	Vector operator+(const Vector& right) const;
	Vector operator-(const Vector& right) const;
	Vector operator*(const Vector& right) const;
	Vector& operator+=(const Vector& right);
	Vector& operator-=(const Vector& right);
	Vector& operator*=(const Vector& right);
	//Scalar
	Vector operator*(const float right) const;
	Vector operator/(const float right) const;
	//Bool
	bool operator==(const Vector& right);
	bool operator!=(const Vector& right);

	float Modulus() const;
	float DotProduct(const Vector& right) const;
};


typedef Vector<2, float> Vec2f;
typedef Vector<3, float> Vec3f;
typedef Vector<4, float> Vec4f;
typedef Vector<2, double> Vec2d;
typedef Vector<3, double> Vec3d;
typedef Vector<4, float> Vec4d;

