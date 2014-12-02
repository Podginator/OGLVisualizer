#include "OGLRectangle.h"

OGLRectangle::OGLRectangle(const Vec2f& position, const Color& color, float height, float width) : _height(height), _width(width),
OGLShape2D(position, color, 4, GL_QUADS)
{
    //init the OGLRectangle to a fixed size
    vertexs[0] = Vec2f(position);
    vertexs[1] = Vec2f(position.X() + width, position.Y());
    vertexs[2] = Vec2f(position.X() + width, position.Y() + height);
    vertexs[3] = Vec2f(position.X(), position.Y() + height);    

    OGLShape2D::GetBoundingBox();
}

OGLRectangle::~OGLRectangle(){}

void OGLRectangle::CenterRotate(float deg)
{
    //Move them towards the center. 
    for (size_t i = 0; i < _size; i++)
    {
        vertexs[i] -= Vec2f((_width*0.5f), (_height*0.5f));
    }

    OGLShape2D::CenterRotate(deg);

    for (size_t i = 0; i < _size; i++)
    {
        vertexs[i] += Vec2f((_width*0.5f), (_height*0.5f));
    }

    //We've changed the shape, so we have to reget the binding box.
    OGLShape2D::GetBoundingBox();
}

void OGLRectangle::Scale(float scale)
{
    for (size_t i = 0; i < _size; i++)
    {
        vertexs[i] -= Vec2f((_width*0.5f), (_height*0.5f));
    }

    OGLShape2D::Scale(scale);

    for (size_t i = 0; i < _size; i++)
    {
        vertexs[i] += Vec2f((_width*0.5f), (_height*0.5f)) * scale;
    }
}
