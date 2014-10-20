#pragma once

#include <math.h>
#include <array>

template<class CRTP,typename T, size_t size>
class VectBase
{
protected:
	void Copy(const VectBase& copied)
	{
		for (int i = 0; i < size; i++)
		{
			crtp().crtp().data[i] = copied[i];
		}
	}

	CRTP& crtp() { return static_cast<CRTP&>(*this); }
	const CRTP& crtp() const { return static_cast<const CRTP&>(*this); }


public:
	template<typename... Args>
	VectBase(Args const&... args)
	{
		std::array<T, size> holder = { args... };
		//Ugly as hell, got to be a better way......
		for (size_t i = 0; i< size; i++)
		{
			crtp().data[i] = holder[i];
		}
	}

	VectBase()
	{
		for (size_t i = 0; i < size; i++)
		{
			crtp().crtp().data[i] = 0;
		}
	};
	VectBase(const VectBase& copy){ Copy(copy); }

	T& operator [](std::size_t const& index){return crtp().data[index];}
	const T& operator [](std::size_t const& index) const { return crtp().data[index]; }


	VectBase& operator= (const VectBase& right) { Copy(copy) };
	//Basic Operators.


	VectBase operator+(const VectBase& right) const
	{
		VectBase<CRTP,T,size> res;
		for (size_t i = 0; i < size; i++)
		{
			res[i] = crtp().data[i] + right[i];
		}

		return res;
	}

	VectBase operator-(const VectBase& right) const
	{
		VectBase<CRTP, T, size> res;
		for (size_t i = 0; i < size; i++)
		{
			res[i] = crtp().data[i] - right[i];
		}

		return res;

	}
	VectBase operator*(const VectBase& right) const
	{
		VectBase<CRTP, T, size> res;
		for (size_t i = 0; i < size; i++)
		{
			res[i] = crtp().data[i] * right[i];
		}

		return res;

	}
	VectBase& operator+=(const VectBase& right)
	{
		for (size_t i = 0; i < size; i++)
		{
			crtp().crtp().data[i] += right[i];
		}

		return *this;
	}
	VectBase& operator-=(const VectBase& right)
	{
		for (size_t i = 0; i < size; i++)
		{
			crtp().crtp().data[i] -= right[i];
		}

		return *this;
	}
	VectBase& operator*=(const VectBase& right)
	{
		for (size_t i = 0; i < size; i++)
		{
			crtp().crtp().data[i] *= right[i];
		}

		return *this;
	}

	//Scalar
	VectBase operator*(const float right) const
	{
		VectBase<CRTP, T, size> res;

		for (size_t i = 0; i < size; i++)
		{
			res[i] = crtp().data[i] * right;
		}

		return res;
	}
	VectBase operator/(const float right) const
	{
		VectBase<CRTP, T, size> res;

		for (size_t i = 0; i < size; i++)
		{
			res[i] = crtp().data[i] * right;
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
			res += crtp().data[i] * crtp().data[i];
		}

		return sqrt(res);
	}
	float DotProduct(const VectBase& right) const
	{
		float res = 0;

		for (size_t i = 0; i < size; i++)
		{
			res += crtp().data[i] + right[i];
		}

		return res;
	}
};


template<typename T, size_t size> 
class Vector : public VectBase<Vector<T, size>, T, size>
{
public:
	T data[size];

	template<typename... Args>
	Vector(Args const&... args) :VectBase(args...)
	{
	}

	float X() const
	{
		return data[0];
	}
	float Y() const
	{
		return data[1];
	}
	float Z() const
	{
		return data[2];
	}
	float W() const
	{
		return data[3];
	}


};


template<typename T>
class Vector<T, 2> : public VectBase<Vector<T, 2>, T, 2>
{
public:
	T data[2];


	template<typename... Args>
	Vector(Args const&... args) :VectBase(args...)
	{
	}


	float X() const
	{
		return data[0];
	}

	float Y() const
	{
		return data[1];
	}

};

template<typename T>
class Vector<T, 3> : public VectBase<Vector<T, 3>, T, 3>
{
public:
	T data[3];


	float X() const
	{
		return data[0];
	}
	void X(float x)
	{
		data[0] = x;
	}
	float Y() const
	{
		return data[1];
	}
	float Z() const
	{
		return data[2];
	}



};




