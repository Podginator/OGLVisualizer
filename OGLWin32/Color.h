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

    Color(const Color& copy)
    {
        red = copy.red;
        blue = copy.blue;
        green = copy.green;
    }

    ~Color(){}

    Color& operator=(const Color& copy)
    {
        if (this != &copy)
        {
            red = copy.red;
            blue = copy.blue;
            green = copy.green;
        }

        return *this;
    }

    Color& operator<< (unsigned int shift);
    Color& operator>> (unsigned int shift);

    void Shade(float percent);
private:
    bool convString(std::string const& str);
};