#include "OGLRectangle3D.h"

OGLRectangle3D::OGLRectangle3D(const Vec3f& position, const Color& color, float height, float width) : _height(height), _width(width),
OGLShape3D(position, color, 4, GL_QUADS)
{
    //init the OGLRectangle to a fixed size
    vertexs[0] = Vec3f(position);
    vertexs[1] = Vec3f(position.X() + width, position.Y(), position.Z());
    vertexs[2] = Vec3f(position.X() + width, position.Y() + height, position.Z());
    vertexs[3] = Vec3f(position.X(), position.Y() + height, position.Z());
}

OGLRectangle3D::~OGLRectangle3D(){}

void OGLRectangle3D::CenterRotate(float deg)
{
    //Move them towards the center. 
    for (size_t i = 0; i < _size; i++)
    {
        vertexs[i] -= Vec3f((_width*0.5f), (_height*0.5f), 0);
    }

    Matrix<float> rotMat = MathHelper::Matrix2Dtransform(deg);
    for (size_t i = 0; i < _size; i++)
    {
        //Move it to the center.
        vertexs[i] -= _position;
        //Then rotate.
        Vec2f Temp = rotMat * Vec2f(vertexs[i].X(), vertexs[i].Y());

        vertexs[i] = Vec3f(Temp.X(), Temp.Y(), _position.Z());
        //Then move back.
        vertexs[i] += _position;

        vertexs[i].Z(_position.Z());
    }

    for (size_t i = 0; i < _size; i++)
    {
        vertexs[i] += Vec3f((_width*0.5f), (_height*0.5f), 0);
    }

    //We've changed the shape, so we have to reget the binding box.
}

void OGLRectangle3D::Scale(float scale)
{
    for (size_t i = 0; i < _size; i++)
    {
        vertexs[i] -= Vec3f((_width*0.5f), (_height*0.5f), 0);
    }

    OGLShape3D::Scale(scale);

    for (size_t i = 0; i < _size; i++)
    {
        vertexs[i] += Vec3f((_width*0.5f), (_height*0.5f), 0) * scale;
    }
}
