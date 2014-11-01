#pragma once

#include "OGLShape.h"
#include "OGLText.h"
#include "OGLRectangle.h"
#include "OGLArc.h"
#include "OGLLine.h"
#include "OGLCircle.h"
#include "DataColumn.h"
#include <vector>

//Initial Base class where Chart will be founded. 
class OGLChart : public Listener, public Renderable
{
protected:
    //We need to define an entry point for all the charts.
    OGLShape* shapes; 
    OGLText* text;
    OGLRectangle* _border;
    std::vector<DataColumn*> data;
    size_t _elemSize;
    void RenderAxis();
    void RenderMisc();
    void RenderShapes();
    void RenderText();
    void InitElements();
    void AddDataSource(DataColumn* _data){ data.push_back(_data); }
    bool MouseInside(int x, int y){ return true; }

public:
    OGLChart();
    void Render();

    bool MouseMove(int x, int y)
    {
        return true;
    }
    bool MouseLBDown(int x, int y)
    {
        return true;
    }
    bool MouseLBUp(int x, int y)
    {
        return true;
    };


};