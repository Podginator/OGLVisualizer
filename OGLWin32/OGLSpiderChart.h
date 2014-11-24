#pragma once
#include "OGLChart.h"

class OGLSpiderChart : public OGLChart
{
public:
    OGLSpiderChart(DataColumn col);
    OGLSpiderChart();
    void AddDataSource(DataColumn col);
    void InitElements();

protected: 
    Vec2f* CreateSpiderVert();
};