#pragma once
#include "OGLChart.h"

class OGLScatterPlot2D : public OGLChart
{
public:
    OGLScatterPlot2D(DataColumn col);
    OGLScatterPlot2D();
    void AddDataSource(DataColumn col);
    void InitElements();
    bool MouseMove(int x, int y)
    {
        OGLChart::GetHighlight(x, y);
        return OGLChart::MouseMove(x, y);
    }
};