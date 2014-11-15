#pragma once

#include "Renderable.h"
#include "Listener.h"
#include "MathHelper.h"
#include <math.h>
#include "Color.h"

class OGLShape : public Renderable, public Listener
{
protected:
    Vec2f _position;
    Color rgb;
    Vec2f* vertexs;
    size_t _size;
    unsigned int _renderType;
    void RenderVertexs(); 

    //Necessary for Bounding Box
    float xBot;
    float xTop;
    float yBot;
    float yTop;


    void Copy(const OGLShape& copy)
    {
        vertexs = new Vec2f[copy._size];
        for (size_t i = 0; i < copy._size; i++)
        {
            vertexs[i] = copy.vertexs[i];
        }
        rgb = copy.rgb;
        _position = copy._position;
        _renderType = copy._renderType;
        _size = copy._size;

        GetBoundingBox();
    }

    bool InsideBounding(int x, int y);

    void GetBoundingBox()
    {
        for (size_t i = 0; i < _size; i++)
        {
            if (vertexs[i].X() > xTop)
            {
                xTop = vertexs[i].X();
            }
            if (vertexs[i].X() < xBot)
            {
                xBot = vertexs[i].X();
            }
            if (vertexs[i].Y() > yTop)
            {
                yTop = vertexs[i].Y();
            }
            if (vertexs[i].Y() < yBot)
            {
                yBot = vertexs[i].Y();
            }
        }
    }

    
public: 
    OGLShape(const Vec2f& position, const Color& color, size_t size, unsigned int renderType) : _position(position), rgb(color), _size(size), _renderType(renderType)
    {
        vertexs = new Vec2f[size];
    };

    OGLShape(const Vec2f& position, const Color& color, size_t size, unsigned int renderType, Vec2f positions[]) : _position(position), _size(size), rgb(color), _renderType(renderType)
    {
        vertexs = new Vec2f[size+1];
        vertexs[0] = position;
        xBot = xBot = _position.X();
        yBot = yTop = _position.Y();

        for (size_t i = 1; i < size; i++)
        {
            vertexs[i] = positions[i - 1];
        }

        GetBoundingBox();
    }

    OGLShape() :rgb(Color(1.0, 1.0, 1.0)){ vertexs = new Vec2f[1]; }

    ~OGLShape()
    {
        delete[] vertexs;
    }

    OGLShape(const OGLShape& copy)
    {
        Copy(copy);
    }

    OGLShape& operator=(const OGLShape& right)
    {
        if (this != &right)
        {
            Copy(right);
        }

        return *this;
    }

    virtual void Render();
    virtual void Rotate(float deg);
    virtual void CenterRotate(float deg);
    virtual void Scale(float deg);
    void Move(float x, float y);
    bool MouseInside(int x, int y);

    bool MouseMove(int x, int y)
    {
        //printf("%d", MouseInside(x,y));
        //MouseInside(x, y);
        return true;
    }

    bool MouseWheel(float deg){ return true; }

    bool MouseLBUp(int x, int y)
    {
        return true;
    }
    bool MouseLBDown(int x, int y)
    {        
        if (MouseInside(x, y))
        {
            rgb >> 1;
        }
        return true;
    }

};