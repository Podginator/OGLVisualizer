#pragma once
#include "Color.h"


Color::Color(std::string const& str)
{
    convString(str);
    alpha = 1.0f;
}

Color::Color(std::string const& str, float _alpha)
{
    convString(str);
    alpha = _alpha;
}

Color& Color::operator<<(unsigned int shift)
{
    red = ((int)(red * 255) << shift);
    red /= 255;
    green = ((int)(red * 255) << shift);
    green /= 255;
    blue = ((int)(red * 255) << shift);
    blue /= 255;
    return *this;
}

Color& Color::operator>> (unsigned int shift)
{
    red = ((int)(red * 255) >> shift);
    red /= 255;
    green = ((int)(red * 255) >> shift);
    green /= 255;
    blue = ((int)(red * 255) >> shift);
    blue /= 255;
    return *this;
}

void Color::Shade(float percent)
{
    red *= 255;
    red *= (100 + percent) / 100;
    green *= 255;
    green *= (100 + percent) / 100;
    blue *= 255;
    blue *= (100 + percent) / 100;

    red = red > 255 ? 1 : red / 255;
    green = green > 255 ? 1 : green / 255;
    blue = blue > 255 ? 1 : blue / 255;
}

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
