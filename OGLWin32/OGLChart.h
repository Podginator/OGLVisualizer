#pragma once

#include "OGLShape.h"
#include "OGLText.h"
#include "OGLRectangle.h"
#include "OGLArc.h"
#include "OGLLine.h"
#include "OGLCircle.h"
#include "DataColumn.h"
#include <vector>
#include <array>

//Initial Base class where Chart will be founded. 
class OGLChart : public Listener, public Renderable
{
protected:
    //We need to define an entry point for all the charts.
    OGLShape* shapes;
    OGLText* text;
    OGLRectangle _border;
    std::vector<DataColumn> data;
    Vec2f _relativePos = Vec2f(0, 0);
    void InitElements();
    size_t elemSize;
    size_t textSize;
   
    bool MouseInside(int x, int y){ return true; }

public:
    OGLChart();
    virtual void Render();
    virtual void AddDataSource(DataColumn _data){ data.push_back(_data); }

    void CenterRotate(float deg);
    void Rotate(float deg);
    void Scale(float scale);
    void Move(float x, float y);

    bool MouseMove(int x, int y)
    {
        if (MouseDown&_border.MouseInside(x,y))
        {
            float displaceX = x - Listener::x ;
            float displaceY = y - Listener::y;
            _relativePos -= Vec2f(displaceX, displaceY);
            Move(displaceX, displaceY);
        }
        Listener::x = float(x);
        Listener::y = float(y);
        return true;
    }
    bool MouseLBDown(int x, int y)
    {   
        MouseDown = true;
        Listener::x = float(x);
        Listener::y = float(y);
        return _border.MouseInside(x,y);
    }
    bool MouseLBUp(int x, int y)
    {
        MouseDown = false;
        return true;
    };

    bool MouseWheel(float deg)
    {
        if (deg > 0)
        {
            Scale(1.1f);
            scale *= 1.1f;
        }
        else
        {
            Scale(0.9f);
            scale *= 0.9f;
        }
        return true;
    }


};