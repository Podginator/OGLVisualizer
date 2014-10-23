#pragma once
#include <string>

struct Proxy
{
	Proxy() 
	{
	}

	Proxy(std::string const& str) 
	{
		val = str;
	}

	Proxy(Proxy const& other)
	{
		val = other.val;
	}

	Proxy(Proxy&& other) 
	{
		std::swap(val, other.val);
	}

	Proxy& operator =(Proxy const& other)
	{
		val = other.val;
		return *this;
	}

	Proxy& operator =(Proxy&& other) {
		std::swap(val, other.val);
		return *this;
	}

private:
	std::string val;
};