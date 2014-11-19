#pragma once
#include <string>

struct Color
{
    float red;
    float green;
    float blue;
    float alpha;

    Color(std::string const& str);
    Color(){}
    Color(float _red, float _green, float _blue) : red(_red), blue(_blue), green(_green), alpha(1.0f){};

    Color(const Color& copy)
    {
        red = copy.red;
        blue = copy.blue;
        green = copy.green;
        alpha = copy.alpha;
    }

    Color(float _red, float _green, float _blue, float _alpha) : red(_red), blue(_blue), green(_green), alpha(_alpha)
    {
        printf("DidYouActivate?");
    };
    Color(std::string const& str, float _alpha);


    ~Color(){}

    Color& operator=(const Color& copy)
    {
        if (this != &copy)
        {
            red = copy.red;
            blue = copy.blue;
            green = copy.green;
            alpha = copy.alpha;
        }

        return *this;
    }

    Color& operator<< (unsigned int shift);
    Color& operator>> (unsigned int shift);

    void Shade(float percent);
private:
    bool convString(std::string const& str);
};