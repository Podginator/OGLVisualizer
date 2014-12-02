#pragma once

#include "OGLShape3D.h"

class OGLLine3D : public OGLShape3D
{
protected:
    Vec3f _endPosition;
public:
    OGLLine3D(const Vec3f& position, const Color& color, const Vec3f& endPos);
    ~OGLLine3D();

    bool            MouseInside(int x, int y);
    bool            MouseMove(int x, int y);
    bool            MouseLBUp(int x, int y);
    bool            MouseLBDown(int x, int y);

};
