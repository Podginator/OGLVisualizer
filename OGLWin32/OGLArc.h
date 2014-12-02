#pragma once

#include "OGLShape2D.h"

class OGLArc : public OGLShape2D
{
public:
    OGLArc(const Vec2f& position, const Color& color, float startTheta, float endTheta, float radius);
    ~OGLArc(){}
    bool MouseMove(int x, int y);
    bool MouseLBUp(int x, int y);
    void Scale(float scale);
protected:
    bool MouseInside(int x, int y);
    float _startTheta;
    float _endTheta;
    float _radius;
    void CreateArc();
};