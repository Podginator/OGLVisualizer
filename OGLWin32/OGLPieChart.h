#pragma once
#include "OGLChart.h"

class OGLPieChart : public OGLChart
{
public:
    OGLPieChart(DataColumn col);
    OGLPieChart();
    void AddDataSource(DataColumn col);
    virtual void InitElements();
    
};