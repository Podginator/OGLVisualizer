#pragma once
#include "OGLChart.h"

class OGLBarChart : public OGLChart
{
public:
    OGLBarChart(DataColumn col);
    OGLBarChart();
    void AddDataSource(DataColumn col);
    void InitElements();

};