#pragma once
#include "OGLChart.h"

OGLChart::OGLChart() : _border(OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750))
{
    _elemSize = 0;
}

void OGLChart::Render()
{
    _border.Render();
    for (size_t i = 0; i < _elemSize; i++)
    {
        shapes[i].Render();
    }

    for (size_t k = 0; k < text.size(); k++)
    {
        text[k].Render();
    }

}

void OGLChart::Scale(float scale)
{
    _border.Scale(scale);
    for (size_t i = 0; i < _elemSize; i++)
    {
        shapes[i].Scale(scale);
    }

    for (size_t k = 0; k < text.size(); k++)
    {
        text[k].Scale(scale);
    }
}

void OGLChart::Rotate(float deg)
{
    _border.Rotate(deg);
    for (size_t i = 0; i < _elemSize; i++)
    {
        shapes[i].Rotate(deg);
    }

    for (size_t k = 0; k < text.size(); k++)
    {
        text[k].Rotate(deg);
    }
}

void OGLChart::CenterRotate(float deg)
{
    _border.CenterRotate(deg);
    for (size_t i = 0; i < _elemSize; i++)
    {
        shapes[i].CenterRotate(deg);
    }

    for (size_t k = 0; k < text.size(); k++)
    {
        text[k].CenterRotate(deg);
    }
}