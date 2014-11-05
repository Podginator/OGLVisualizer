#pragma once
#include "OGLChart.h"

class OGLPieChart : public OGLChart
{
public:
    OGLPieChart(DataColumn* col);
    OGLPieChart();
    void AddDataSource(DataColumn* col);
    void InitElements();

    bool MouseMove(int x, int y)
    {
        return true;
    }
    bool MouseLBDown(int x, int y)
    {
        return true;
    }
    bool MouseLBUp(int x, int y)
    {
        return true;
    };
protected:
    std::array<Color, 9> colors;
};