#pragma once
#include <string>

struct Color
{
	float red;
	float green;
	float blue;

	Color(std::string const& str)
	{
		convString(str);
	}

	Color(float _red, float _green, float _blue) : red(_red), blue(_blue), green(_green){};

	Color& operator<< (unsigned int shift)
	{
		red = ((int)(red * 255) << shift);
		red /= 255;
		green = ((int)(red * 255) << shift);
		green /= 255;
		blue = ((int)(red * 255) << shift);
		blue /= 255;
		return *this;
	}	
	Color& operator>> (unsigned int shift)
	{
		red = ((int)(red * 255) >> shift);
		red /= 255;
		green = ((int)(red * 255) >> shift);
		green /= 255;
		blue = ((int)(red * 255) >> shift);
		blue /= 255;
		return *this;
	}
private:
	bool convString(std::string const& str);
};