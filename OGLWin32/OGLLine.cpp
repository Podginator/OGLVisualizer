#pragma once

#include "OGLLine.h"

OGLLine::OGLLine(const Vec2f& position, const Color& color, const Vec2f& endPos) :_endPosition(endPos), OGLShape(position, color, 3, GL_LINES)
{
    vertexs[0] = _position;
    vertexs[1] = _endPosition;
}

bool OGLLine::MouseInside(int x, int y)
{
    return x == _position.X() && (y > _position.Y() && y < _endPosition.Y());
}


bool OGLLine::MouseMove(int x, int y)
{
    return true;
}
bool OGLLine::MouseLBUp(int x, int y)
{
    return true;
}
bool OGLLine::MouseLBDown(int x, int y)
{
    CenterRotate(1.0f);
    return true;
}
