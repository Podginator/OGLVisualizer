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
    OGLRectangle _border;
    std::vector<OGLText> text;
    std::vector<DataColumn> data;
    size_t _elemSize;
    void InitElements();
   
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
            Move(displaceX, displaceY);
        }
        Listener::x = x;
        Listener::y = y;
        return true;
    }
    bool MouseLBDown(int x, int y)
    {   
        MouseDown = true;
        Listener::x = x;
        Listener::y = y;
        return true;
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
            Scale(1.1);
        }
        else
        {
            Scale(0.9);
        }
        return true;
    }


};