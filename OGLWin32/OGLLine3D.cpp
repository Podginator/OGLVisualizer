#pragma once

#include "OGLLine3D.h"

OGLLine3D::OGLLine3D(const Vec3f& position, const Color& color, const Vec3f& endPos) :_endPosition(endPos), OGLShape3D(position, color, 2, GL_LINES)
{
    vertexs[0] = _position;
    vertexs[1] = _endPosition;
}

bool OGLLine3D::MouseInside(int x, int y)
{
    return x == _position.X() && (y > _position.Y() && y < _endPosition.Y());
}


bool OGLLine3D::MouseMove(int x, int y)
{
    return true;
}
bool OGLLine3D::MouseLBUp(int x, int y)
{
    return true;
}
bool OGLLine3D::MouseLBDown(int x, int y)
{
    //CenterRotate(1.0f);
    return true;
}
