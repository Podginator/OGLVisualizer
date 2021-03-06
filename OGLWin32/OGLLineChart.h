#pragma once

#include "OGLChart.h"

class OGLLineChart : public OGLChart
{
public:
    OGLLineChart(DataColumn col);
    OGLLineChart();
    void AddDataSource(DataColumn col);
    void InitElements();
};