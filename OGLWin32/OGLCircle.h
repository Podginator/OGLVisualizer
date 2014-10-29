#pragma once

#include "OGLArc.h"

class OGLCircle : public OGLArc
{
public:
    OGLCircle(const Vec2f& position,const Color& color, float radius) :OGLArc(position, color, 0.f, 360.f, radius){}
    ~OGLCircle();

    bool OGLCircle::MouseInside(int x, int y)
    {
        if (((x - _position.X())*(x - _position.X()) +
            (y - _position.Y()) * (y - _position.Y()) <=
            (_radius*_radius)))
        {
            //Reduce to this instead because if we're inside a circle the angle is irrelevant
            //And the other is very intensive.
            return true;
        }
        return false;
    }
};