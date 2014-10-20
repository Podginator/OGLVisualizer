#pragma once

#include <math.h>
#include <array>

template<class CRTP,typename T, size_t size>
class VectBase
{
protected:
	T data[size];
	void Copy(const VectBase& copied)
	{
		for (int i = 0; i < size; i++)
		{
			data[i] = copied.data[i];
		}
	}

public:
	template<typename... Args>
	VectBase(Args const&... args)
	{
		std::array<T, size> holder = { args... };
		//Ugly as hell, got to be a better way......
		for (size_t t = 0; t < size; t++)
		{
			data[t] = holder[t];
		}
	}

	VectBase()
	{
		for (size_t i = 0; i < size; i++)
		{
			data[i] = 0;
		}
	};
	VectBase(const VectBase& copy){ Copy(copy); }

	T& operator [](std::size_t const& index){return data[index];}
	const T& operator [](std::size_t const& index) const { return data[index]; }


	VectBase& operator= (const VectBase& right) { Copy(copy) };
	//Basic Operators.


	VectBase operator+(const VectBase& right) const
	{
		VectBase<CRTP,T,size> res;
		for (size_t i = 0; i < size; i++)
		{
			res.data[i] = data[i] + right.data[i];
		}

		return res;
	}

	VectBase operator-(const VectBase& right) const
	{
		VectBase<CRTP, T, size> res;
		for (size_t i = 0; i < size; i++)
		{
			res.data[i] = data[i] - right.data[i];
		}

		return res;

	}
	VectBase operator*(const VectBase& right) const
	{
		VectBase<CRTP, T, size> res;
		for (size_t i = 0; i < size; i++)
		{
			res.data[i] = data[i] * right.data[i];
		}

		return res;

	}
	VectBase& operator+=(const VectBase& right)
	{
		for (size_t i = 0; i < size; i++)
		{
			data[i] += right.data[i];
		}

		return *this;
	}
	VectBase& operator-=(const VectBase& right)
	{
		for (size_t i = 0; i < size; i++)
		{
			data[i] -= right.data[i];
		}

		return *this;
	}
	VectBase& operator*=(const VectBase& right)
	{
		for (size_t i = 0; i < size; i++)
		{
			data[i] *= right.data[i];
		}

		return *this;
	}

	//Scalar
	VectBase operator*(const float right) const
	{
		VectBase<CRTP, T, size> res;

		for (size_t i = 0; i < size; i++)
		{
			res.data[i] = data[i] * right;
		}

		return res;
	}
	VectBase operator/(const float right) const
	{
		VectBase<CRTP, T, size> res;

		for (size_t i = 0; i < size; i++)
		{
			res.data[i] = data[i] * right;
		}

		return res;
	}
	//Bool
	bool operator==(const VectBase& right){
		return true;
	}
	bool operator!=(const VectBase& right)
	{
		return false;
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
			res += data[i] + right.data[i];
		}

		return res;
	}
};


template<typename T, size_t size> 
class Vector : public VectBase<Vector<T, size>, T, size>
{
public:
	template<typename... Args>
	Vector(Args const&... args) :VectBase(args...)
	{
	}

	union 
	{
		T data[size];
		struct {
			T x, y, z, w;
		};
	};
};


template<typename T>
class Vector<T, 2> : public VectBase<Vector<T, 2>, T, 2>
{
public:
	template<typename... Args>
	Vector(Args const&... args) :VectBase(args...)
	{
	}

	union
	{
		T data[2];
		struct {
			T x, y;
		};
	};
};

template<typename T>
class Vector<T, 3> : public VectBase<Vector<T, 3>, T, 3>
{
public:
	template<typename... Args>
	Vector(Args const&... args) :VectBase(args...)
	{
	}

	union
	{
		T data[3];
		struct {
			T x, y, w;
		};
	};
};




