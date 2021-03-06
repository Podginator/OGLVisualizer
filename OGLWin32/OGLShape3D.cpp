#include "OGLShape3D.h"
#include "OGLWindow.h"
#include <gl/GLU.h>
OGLShape3D::OGLShape3D(const Vec3f& position, const Color& color, size_t size, unsigned int renderType) :_position(position), OGLShape(color,size,renderType)
{
    vertexs = new Vec3f[size];
}
OGLShape3D::OGLShape3D()
{

}

void OGLShape3D::Render()
{

    //GLBegin basically just takes a Unsigned int Macro
    //So can pass it in as a variable
    //glDisable(GL_MULTISAMPLE);

    glBegin(_renderType);
    RenderVertexs();
    glEnd();    

}

void OGLShape3D::RenderVertexs()
{
    glColor4f(rgb.red, rgb.green, rgb.blue, rgb.alpha);
    for (size_t i = 0; i < _size; i++)
    {
        glVertex3f(vertexs[i].X(), vertexs[i].Y(), vertexs[i].Z());
    }


}

void OGLShape3D::Move(float x, float y)
{
    _position += Vec3f(x, y, 0);

    for (size_t i = 0; i < _size; i++)
    {
        vertexs[i] += Vec3f(x, y, 0);
    }
}

void OGLShape3D::MoveRel(float x, float y)
{
    _position += Vec3f(x, y, 0);

    for (size_t i = 0; i < _size; i++)
    {
        vertexs[i] += Vec3f(x, y, 0);
    }
}

void OGLShape3D::MoveZ(float z)
{
    _position += Vec3f(0,0,z);

    for (size_t i = 0; i < _size; i++)
    {
        vertexs[i] += Vec3f(0, 0, z); 
    }
}

void OGLShape3D::Scale(float scale)
{
    //Listener::scale *= scale;

    float tempZ = _position.Z();
    _position = _position*scale;
    _position.Z(tempZ);

    for (size_t i = 0; i < _size; i++)
    {
        tempZ = vertexs[i].Z();
        vertexs[i] -= _position;
        
        //Then scale.
        vertexs[i] = vertexs[i] * scale;
        //Then move back.
        vertexs[i] += _position * scale;
        vertexs[i].Z(tempZ);
    }
}
