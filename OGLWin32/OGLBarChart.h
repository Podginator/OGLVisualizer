#pragma once
#include "OGLChart.h"

class OGLBarChart : public OGLChart
{
public:
    OGLBarChart(DataColumn col);
    OGLBarChart();
    void AddDataSource(DataColumn col);
    void InitElements();
    bool MouseMove(int x, int y)
    {
        GetHighlight(x, y);
        return OGLChart::MouseMove(x, y);
    }
    
protected:
    size_t MaxDist();
    void GetHighlight(int x, int y);

};