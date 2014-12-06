#pragma once
#include "OGLShape.h"
class OGLShape3D : public OGLShape
{
protected:
    Vec3f _position;
    Vec3f* vertexs;
    void RenderVertexs(); 
    void Copy(const OGLShape3D& copy)
    {
        vertexs = new Vec3f[copy._size];
        for (size_t i = 0; i < copy._size; i++)
        {
            vertexs[i] = copy.vertexs[i];
        }
        rgb = copy.rgb;
        _position = copy._position;
        _renderType = copy._renderType;
        _size = copy._size;
    }

public:
    OGLShape3D(const Vec3f& position, const Color& color, size_t size, unsigned int renderType);
    OGLShape3D();
    virtual void Render();
    virtual void Rotate(float deg){}
    virtual void CenterRotate(float deg){}
    virtual void Scale(float deg);
    virtual void MoveZ(float z);
    virtual void MoveRel(float x, float y);
    void Move(float x, float y);
    bool MouseInside(int x, int y){
        return true;
    }

    bool MouseMove(int x, int y)
    {
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