#pragma once
#include <string>

struct Color
{
    float red;
    float green;
    float blue;

    Color(std::string const& str);
    Color(){}
    Color(float _red, float _green, float _blue) : red(_red), blue(_blue), green(_green){};

    Color& operator<< (unsigned int shift);
    Color& operator>> (unsigned int shift);

    void Shade(float percent);
private:
    bool convString(std::string const& str);
};