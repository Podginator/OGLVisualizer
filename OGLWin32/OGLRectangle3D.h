#pragma once
#include "OGLShape3D.h"
class OGLRectangle3D : public OGLShape3D
{
private:
    float _width;
    float _height;

public:
    OGLRectangle3D(const Vec3f& position, const Color& color, float height, float width);
    ~OGLRectangle3D();

    void            CenterRotate(float deg);
    void            Scale(float scale);
};