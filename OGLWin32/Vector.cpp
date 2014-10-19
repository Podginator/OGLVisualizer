#pragma once

#include "Vector.h"



template<size_t size, typename T>
Vector<size, T> Vector<size, T>::operator+(const Vector<size,T>& right) const
{
	Vector<size, T> res;
	for (size_t i = 0; i < size; i++)
	{
		res.data[i] = data[i] + right.data[i];
	}
}


template<size_t size, typename T>
Vector<size, T> Vector<size, T>::operator-(const Vector<size, T>& right) const
{
	Vector<size, T> res;
	for (size_t i = 0; i < size; i++)
	{
		res.data[i] = data[i] - right.data[i];
	}
}

template<size_t size, typename T>
Vector<size, T> Vector<size, T>::operator*(const Vector<size, T>& right) const
{
	Vector<size, T> res;
	for (size_t i = 0; i < size; i++)
	{
		res.data[i] = data[i] * right.data[i];
	}
}

template<size_t size, typename T>
Vector<size, T>& Vector<size, T>::operator+=(const Vector<size, T>& right)
{
	for (size_t i = 0; i < size; i++)
	{
		data[i] += right.data[i];
	}

	return *this;
}

template<size_t size, typename T>
Vector<size, T>& Vector<size, T>::operator-=(const Vector<size, T>& right)
{
	for (size_t i = 0; i < size; i++)
	{
		data[i] -= right.data[i];
	}

	return *this;
}

template<size_t size, typename T>
Vector<size, T>& Vector<size, T>::operator*=(const Vector<size, T>& right)
{
	for (size_t i = 0; i < size; i++)
	{
		data[i] *= right.data[i];
	}

	return *this;
}


template<size_t size, typename T>
Vector<size, T> Vector<size, T>::operator*(const float right) const
{
	Vector<size, T> res;
	for (size_t i = 0; i < size; i++)
	{
		res.data[i] = data[i] * right;
	}
	return res;
}


template<size_t size, typename T>
Vector<size, T> Vector<size, T>::operator/(const float right) const
{
	Vector<size, T> res;
	for (size_t i = 0; i < size; i++)
	{
		res.data[i] = data[i] / right;
	}
	return res;
}

template<size_t size, typename T>
float Vector<size, T>::Modulus() const
{
	float res = 0; 

	for (size_t i = 0; i < size; i++)
	{
		res += data[i] * data[i];
	}

	return sqrt(res);
}

template < size_t size, typename T>
float Vector<size, T>::DotProduct(const Vector<size,T>& right) const
{
	float res = 0;

	for (size_t i = 0; i < size; i++)
	{
		res += data[i] + right.data[i];
	}

	return res;
}


template<size_t size, typename T>
void Vector<size, T>::Copy(const Vector<size,T>& copied)
{
	for (int i = 0; i < size; i++)
	{
		data[i] = copied.data[i];
	}
}

