#pragma once
#include "OGLShape2D.h"
class OGLRectangle : public OGLShape2D
{
    private:
        float _width;
        float _height;

    public:
                        OGLRectangle(const Vec2f& position, const Color& color, float height, float width);
                        ~OGLRectangle();

        void            CenterRotate(float deg);
        void            Scale(float scale);
};