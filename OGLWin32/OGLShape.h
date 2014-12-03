#pragma once

#include "Renderable.h"
#include "Listener.h"
#include "MathHelper.h"
#include <math.h>
#include <vector>
#include "Color.h"

class OGLShape : public Renderable, public Listener
{
protected:
    Color rgb;
    size_t _size;
    unsigned int _renderType;
    void RenderVertexs(); 


    virtual void Copy(const OGLShape& copy)
    {
        _renderType = copy._renderType;
        _size = copy._size;
    }

    bool InsideBounding(int x, int y);


    
public: 
    OGLShape(const Color& color, size_t size, unsigned int renderType): rgb(color), _size(size), _renderType(renderType)
    {
    };


    OGLShape() :rgb(Color(1.0, 1.0, 1.0)){}

    ~OGLShape()
    {
        //delete[] vertexs;
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

    virtual void Render() = 0;
    virtual void Rotate(float deg) = 0;
    virtual void CenterRotate(float deg) = 0;
    virtual void Scale(float deg) = 0;
    void SetOpacity(float n){ rgb.alpha -= n; }
    void Move(float x, float y) = 0;
    bool MouseInside(int x, int y) = 0;

    bool MouseMove(int x, int y)
    {
		MouseIn = MouseInside(x, y) ? true : false;
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