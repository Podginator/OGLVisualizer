#pragma once
#include "OGLChart.h"

class OGLPieChart : public OGLChart
{
public:
    OGLPieChart(DataColumn* col) :OGLChart(col)
    {
        _border = new OGLRectangle(Vec2f(0, 0), Color(1.0, 1.0, 1.0), 500, 500);
    }

    void Render()
    {
        _border->Render();
    }

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
};