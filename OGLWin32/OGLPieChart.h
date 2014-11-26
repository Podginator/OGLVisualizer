#pragma once
#include "OGLChart.h"

class OGLPieChart : public OGLChart
{
public:
    OGLPieChart(DataColumn col);
    OGLPieChart();
    void AddDataSource(DataColumn col);
    virtual void InitElements();
    bool MouseMove(int x, int y)
    {
        OGLChart::GetDistHighlight(x, y);
        return OGLChart::MouseMove(x, y);
    }
    
};