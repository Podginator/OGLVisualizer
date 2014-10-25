#pragma once
#include "Color.h"


bool Color::convString(std::string const& str)
{
	if (str.length() != 7)
	{
		//Not a valid string, instantiate as 0 0 0 
		red = 0.f;
		green = 0.f;
		blue = 0.f;
		return false;
	}
	char * p;
	unsigned int toHex = strtol(str.substr(1).c_str(), &p, 16);

	//Do some bitshifting to expose the correct bits then convert to 1.0.
	red = ((toHex & 0xFF0000) >> 16) / 255.0f;
	green = ((toHex & 0xFF00) >> 8) / 255.0f;
	blue = (toHex & 0xFF) / 255.0f;

	return true;
}
