#pragma once
#include "OGLChart.h"

class OGLSpiderChart : public OGLChart
{
public:
    OGLSpiderChart(DataColumn col);
    OGLSpiderChart();
    void AddDataSource(DataColumn col);
    void InitElements();
    bool MouseMove(int x, int y);
protected: 
    void Clear();
    std::vector<Vec2f> CreateSpiderVert(int size);
};