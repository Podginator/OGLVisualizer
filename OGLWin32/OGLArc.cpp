#pragma once

#include "OGLArc.h"


OGLArc::OGLArc(const Vec2f& position, const Color& color, float startTheta, float endTheta, float radius)
:OGLShape2D(position, color, (int)(endTheta-startTheta)+3, GL_TRIANGLE_FAN)
{
    _startTheta = startTheta;
    _endTheta = endTheta;
    _radius = radius;
    CreateArc();
    OGLShape2D::GetBoundingBox();
}


void OGLArc::CreateArc()
{
    //An Arc will have it's first vertex in the center of the circle.
    vertexs[0] = _position; 
    //Vertex one will be Radius away from the first point, so we assume it's 0deg away,
    //Which is the same as moving the Y _Radius away
    int i;
    for (i = 0; i <= (_endTheta-_startTheta); i++)
    {
        //We then repeat this process 
        vertexs[1 + i] = MathHelper::Matrix2Dtransform(-(_startTheta + i)) * Vec2f(0, _radius);
        vertexs[1 + i] += _position;
    }

    vertexs[1+i] = MathHelper::Matrix2Dtransform(-_endTheta) * Vec2f(0, _radius);
    vertexs[1+i] += _position;

}


void OGLArc::Scale(float scale)
{
    OGLShape2D::Scale(scale);
    _radius *= scale;
}

bool OGLArc::MouseInside(int x, int y)
{
    if (!OGLShape2D::InsideBounding(x, y))
    {
        return false;
    }

    if (((x - _position.X())*(x - _position.X()) +
        (y - _position.Y()) * (y - _position.Y()) <=
        (_radius*_radius)))
    {
        //So now we need to determine where the angle is from the center point.
        float angle = atan2f(_radius, 0) - atan2f(y - _position.Y(), x - _position.X());
        angle *= 360 / (2 * MathHelper::Pi());
        angle = angle < 0 ? angle + 360 : angle;
        //Then we can return true of false
        if (angle >= _startTheta && angle <= (_endTheta))
        {
            return true;
        }
    }

    return false;
}

bool OGLArc::MouseLBUp(int x, int y)
{

    return true;
}