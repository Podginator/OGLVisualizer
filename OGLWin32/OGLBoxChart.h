#pragma once
#include "OGLChart.h"

class OGLBoxChart : public OGLChart
{
public:
    OGLBoxChart(DataColumn col);
    OGLBoxChart();
    void AddDataSource(DataColumn col);
    void InitElements();
    bool MouseMove(int x, int y)
    {
        GetHighlight(x, y);
        return OGLChart::MouseMove(x, y);
    }

protected:
    float GetAverage();
    float GetMedian();
    float GetStdDev();
};