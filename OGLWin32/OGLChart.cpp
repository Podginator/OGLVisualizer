#pragma once
#include "OGLChart.h"

OGLChart::OGLChart()
{
    _border = new OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750);
    _elemSize = 0;
}

void OGLChart::Render()
{
    _border->Render();
    for (size_t i = 0; i < _elemSize; i++)
    {
        shapes[i].Render();
    }
    for (size_t i = 0; i < _elemSize / 2; i++)
    {
        text[i].Render();
    }
}