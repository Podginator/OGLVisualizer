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
        GetHighlight(x, y);
        return OGLChart::MouseMove(x, y);
    }
protected:
    void GetHighlight(int x, int y);
    size_t DataSize();
    
};