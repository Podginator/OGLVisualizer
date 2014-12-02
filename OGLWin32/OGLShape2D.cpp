#include "OGLShape2D.h"

void OGLShape2D::Rotate(float deg)
{
    Matrix<float> rotMat = MathHelper::Matrix2Dtransform(deg);

    for (size_t i = 0; i < _size; i++)
    {
        //Just rotates from center as origin. 
        vertexs[i] = rotMat * vertexs[i];
    }

    OGLShape2D::GetBoundingBox();
}

void OGLShape2D::CenterRotate(float deg)
{
    Matrix<float> rotMat = MathHelper::Matrix2Dtransform(deg);
    for (size_t i = 0; i < _size; i++)
    {
        //Move it to the center.
        vertexs[i] -= _position;
        //Then rotate.
        vertexs[i] = rotMat * vertexs[i];
        //Then move back.
        vertexs[i] += _position;
    }

    OGLShape2D::GetBoundingBox();
}

void OGLShape2D::Move(float x, float y)
{
    _position += Vec2f(x, y);

    for (size_t i = 0; i < _size; i++)
    {
        vertexs[i] += Vec2f(x, y);
    }

    OGLShape2D::GetBoundingBox();
}

void OGLShape2D::Scale(float scale)
{

    if (Listener::keys[16]){ return; }
    _position = _position*scale;

    for (size_t i = 0; i < _size; i++)
    {
        vertexs[i] -= _position;
        //Then scale.
        vertexs[i] = vertexs[i] * scale;
        //Then move back.
        vertexs[i] += _position * scale;
    }
    OGLShape2D::GetBoundingBox();
}

void OGLShape2D::Render()
{

    //GLBegin basically just takes a Unsigned int Macro
    //So can pass it in as a variable
    //glDisable(GL_MULTISAMPLE);
    glBegin(_renderType);
        RenderVertexs();
    glEnd();
}

void OGLShape2D::RenderVertexs()
{
    glPushMatrix();


    glColor4f(rgb.red, rgb.green, rgb.blue, rgb.alpha);
    for (size_t i = 0; i < _size; i++)
    {
        glVertex3f(vertexs[i].X(), vertexs[i].Y(), -1.0f);
    }
    glPopMatrix();
}


bool OGLShape2D::InsideBounding(int x, int y)
{
    if (x < xBot || x > xTop || y < yBot || y > yTop)
    {
        return false;
    }
    return true;
}
bool OGLShape2D::MouseInside(int x, int y)
{
    //First we test the bounding box cast around the object, this is a very
    //mathematically unintensive process, meaning when we loop through shapes
    //later we won't have problems.
    if (!InsideBounding(x, y))
    {
        return false;
    }

    //Otherwise we have to do a line intersection test.
    //How many times do we hit an edge of the poly?
    int edgeHit = 0;
    //We start at point vertexs[_size] connecting to vertexs[0], hence K = size-1;
    size_t  k = _size - 1;
    //Then we have to loop through all the Vertexs we have
    //Based on the lecture from 20/10/2014
    for (size_t i = 0; i < _size; i++)
    {
        //First we check whether it is between the vertexs Y locations, if not, no point of continuing.
        if (((vertexs[i].Y() > y) && (vertexs[k].Y() < y)) || ((vertexs[i].Y() < y) && (vertexs[k].Y() > y)))
        {
            //Then we check if the X location is less than the X location of the point between Vec[i] and Vec[k], if it is, it will eventually intersect.
            //calculating where that would be based on the Y position. Based on
            // http://gamedev.stackexchange.com/a/57746
            if (x < vertexs[i].X() + (vertexs[k].X() - vertexs[i].X()) * (y - vertexs[i].Y()) / (vertexs[k].Y() - vertexs[i].Y()))
            {
                edgeHit++;
            }
        }
        //Then we make sure that for the next cycle K is the one before the previous. ie the vector that i was this time.
        k = i;
    }

    return (edgeHit % 2);
}