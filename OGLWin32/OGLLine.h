#pragma once

#include "OGLShape.h"

class OGLLine : public OGLShape
{
protected:
    Vec2f _endPosition;
public:
    OGLLine(const Vec2f& position, const Color& color, const Vec2f& endPos);
    ~OGLLine();

    bool            MouseMove(int x, int y);
    bool            MouseLBUp(int x, int y);
    bool            MouseLBDown(int x, int y);
};
