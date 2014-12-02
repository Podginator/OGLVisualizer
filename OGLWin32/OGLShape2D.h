#pragma once
#include "OGLShape.h"

class OGLShape2D : public OGLShape
{
protected:
    Vec2f _position;
    Vec2f* vertexs;
    void RenderVertexs();
    void Copy(const OGLShape2D& copy)
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

        OGLShape2D::GetBoundingBox();
    }

    float xBot;
    float xTop;
    float yBot;
    float yTop;

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
    OGLShape2D(const Vec2f& position, const Color& color, size_t size, unsigned int renderType) :_position(position), OGLShape(color, size, renderType)
    {
        vertexs = new Vec2f[size];
    }

    OGLShape2D(const Vec2f& position, const Color& color, size_t size, unsigned int renderType, Vec2f positions[]) : _position(position), OGLShape(color, size, renderType)
    {
        vertexs = new Vec2f[size + 1];
        vertexs[0] = position;
        xBot = xBot = _position.X();
        yBot = yTop = _position.Y();

        for (size_t i = 1; i < size; i++)
        {
            vertexs[i] = positions[i - 1];
        }

        OGLShape2D::GetBoundingBox();
    }

    OGLShape2D(const Vec2f& position, const Color& color, size_t size, unsigned int renderType, std::vector<Vec2f> positions) : _position(position), OGLShape(color, size, renderType)
    {
        vertexs = new Vec2f[size];
        //vertexs[0] = position;
        xBot = xBot = _position.X();
        yBot = yTop = _position.Y();

        for (size_t i = 0; i < size; i++)
        {
            vertexs[i] = positions[i];
        }

        OGLShape2D::GetBoundingBox();
    }

    OGLShape2D(){ vertexs = new Vec2f[1]; }

    OGLShape2D(const OGLShape2D& copy)
    {
        Copy(copy);
    }

    OGLShape2D& operator=(const OGLShape2D& right)
    {
        if (this != &right)
        {
            Copy(right);
        }

        return *this;
    }

    ~OGLShape2D()
    {
        delete[] vertexs;
    }

    virtual void Render();
    virtual void Rotate(float deg);
    virtual void CenterRotate(float deg);
    virtual void Scale(float deg);
    void Move(float x, float y);
    bool MouseInside(int x, int y);

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