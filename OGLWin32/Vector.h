#pragma once

#include <math.h>
#include <array>

template<typename T, size_t size>
class VectBase
{
protected:

	std::array<T, size> data;

	void Copy(const VectBase& copied)
	{
		for (int i = 0; i < size; i++)
		{
			data[i] = copied[i];
		}
	}

public:
	template<typename... Args>
	VectBase(Args const&... args)
	{
		if (sizeof...(args) > 0)
		{
			data = { args... };
		}
		else
		{
			for (size_t i = 0; i < size; i++)
			{
				data[i] = 0;
			}
		}
	}

	VectBase(const VectBase& copy){ Copy(copy); }

	T& operator [](std::size_t const& index){return data[index];}
	const T& operator [](std::size_t const& index) const { return data[index]; }


	VectBase& operator= (const VectBase& right) { Copy(right); return *this; };
	//Basic Operators.


	VectBase operator+(const VectBase& right) const
	{
		VectBase<CRTP,T,size> res;
		for (size_t i = 0; i < size; i++)
		{
			res[i] = data[i] + right[i];
		}

		return res;
	}

	VectBase operator-(const VectBase& right) const
	{
		VectBase<CRTP, T, size> res;
		for (size_t i = 0; i < size; i++)
		{
			res[i] = data[i] - right[i];
		}

		return res;

	}
	VectBase operator*(const VectBase& right) const
	{
		VectBase<CRTP, T, size> res;
		for (size_t i = 0; i < size; i++)
		{
			res[i] = data[i] * right[i];
		}

		return res;

	}
	VectBase& operator+=(const VectBase& right)
	{
		for (size_t i = 0; i < size; i++)
		{
			data[i] += right[i];
		}

		return *this;
	}
	VectBase& operator-=(const VectBase& right)
	{
		for (size_t i = 0; i < size; i++)
		{
			data[i] -= right[i];
		}

		return *this;
	}
	VectBase& operator*=(const VectBase& right)
	{
		for (size_t i = 0; i < size; i++)
		{
			data[i] *= right[i];
		}

		return *this;
	}

	//Scalar
	VectBase operator*(const float right) const
	{
		VectBase<CRTP, T, size> res;

		for (size_t i = 0; i < size; i++)
		{
			res[i] = data[i] * right;
		}

		return res;
	}
	VectBase operator/(const float right) const
	{
		VectBase<CRTP, T, size> res;

		for (size_t i = 0; i < size; i++)
		{
			res[i] = data[i] * right;
		}

		return res;
	}
	//Bool
	bool operator==(const VectBase& right){
		for (size_t i = 0; i < size; i++)
		{
			if (data[i] != right[0])
			{
				return false;
			}
		}
		return true;
	}
	bool operator!=(const VectBase& right)
	{
		return !(operator==(right));
	}

	float Modulus() const
	{
		float res = 0;

		for (size_t i = 0; i < size; i++)
		{
			res += data[i] * data[i];
		}

		return sqrt(res);
	}
	float DotProduct(const VectBase& right) const
	{
		float res = 0;

		for (size_t i = 0; i < size; i++)
		{
			res += data[i] + right[i];
		}

		return res;
	}
};


template<typename T, size_t size> 
class Vector : public VectBase<T, size>
{
public:
	template<typename... Args>
	Vector(Args const&... args) :VectBase(args...)
	{
	}

};


//There is currently an ICE for variadic constructors and Arrays. This means I've created an Initializer for each
//Implementation. This is piss poor.
//TODO: Look for a work around?
template<typename T>
class Vector<T, 2> : public VectBase<T, 2>
{
public:
	Vector(T x, T y) :VectBase(x,y)
	{
	}

	Vector() :VectBase(){}

	float X() const
	{
		return VectBase::data[0];
	}
	void X(T x)
	{
		VectBase::data[0] = x
	}
	float Y() const
	{
		return VectBase::data[1];
	}
	void Y(T y)
	{
		VectBase::data[1] = y
	}
};

template<typename T>
class Vector<T, 3> : public VectBase<T, 3>
{
public:
	Vector(T x, T y, T z) :VectBase(x, y, z)
	{
	}

	Vector() :VectBase(){}

	float X() const
	{
		return VectBase::data[0];
	}
	void X(T x)
	{
		VectBase::data[0] = x
	}
	float Y() const
	{
		return VectBase::data[1];
	}
	void Y(T y)
	{
		VectBase::data[1] = y
	}
	float Z() const
	{
		return VectBase::data[2];
	}
	void Z(T z)
	{
		VectBase::data[2] = z
	}

	Vector<T, 3> CrossProduct(const Vector<T, 3>& right)
	{
		Vector<T, 3> res;

		res.X(data[1] * right[2] - right[1] * data[2]);
		res.Y(right[0] * data[2] - data[0] * right[2]);
		res.Z(data[0] * right[1] - data[1] * right[0]);

		return res;
	}
};

template<typename T>
class Vector<T, 4> : public VectBase<T, 4>
{
public:
	Vector(T x, T y, T z, T w) :VectBase(x, y, z, w)
	{
	}

	Vector() :VectBase(){}

	float X() const
	{
		return VectBase::data[0];
	}
	void X(T x)
	{
		VectBase::data[0] = x
	}
	float Y() const
	{
		return VectBase::data[1];
	}
	void Y(T y)
	{
		VectBase::data[1] = y
	}
	float Z() const
	{
		return VectBase::data[2];
	}
	void Z(T z)
	{
		VectBase::data[2] = z
	}
	float W() const
	{
		return VectBase::data[3];
	}
	void W(T w)
	{
		VectBase::data[3] = w;
	}
};



typedef Vector<float, 2> Vec2f;
typedef Vector<float, 3> Vec3f;
typedef Vector<float, 4> Vec4f;
