#pragma once
#include "Color.h"

Color::Color(std::string const& str)
{
	convString(str);
	
}

bool Color::convString(std::string const& str)
{

	if (str.length() != 7)
	{
		//Not a valid string, instantiate as 0 0 0 
		red = 0.0f;
		green = 0.f;
		blue = 0.f;
		return false;
	}
	char * p;
	unsigned int toHex = strtol(str.substr(1).c_str(), &p, 16);

	printf(str.substr(1).c_str());
	red = ((toHex & 0xFF0000) >> 16) / 255.0f;
	green = ((toHex & 0xFF00) >> 8) / 255.0f;
	blue = (toHex & 0xFF) / 255.0f;


	printf("R:: %f", red*255);
	printf("G:: %f", green*255);
	printf("B:: %f\n", blue*255);
	return true;
}
