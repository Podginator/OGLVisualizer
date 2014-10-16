#pragma once
#include <string>

struct Proxy
{
	Proxy(std::string const& str)
	{
		val = str;
	}

	template<typename T>
	operator T()
	{
		T ret;
		return std::istringstream(val) >> ret ? ret : T();
	}

private:
	std::string val;
};