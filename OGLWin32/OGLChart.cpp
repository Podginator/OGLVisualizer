#pragma once
#include "OGLChart.h"

OGLChart::OGLChart() : _border(OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750))
{
    textSize = 0;
    elemSize = 0;
}

void OGLChart::Render()
{
    _border.Render();
    for (size_t i = 0; i < elemSize; i++)
    {
        shapes[i].Render();
    }

    for (size_t k = 0; k < textSize; k++)
    {
        text[k].Render();
    }

}

void OGLChart::Scale(float scale)
{
    _border.Scale(scale);
    for (size_t i = 0; i < elemSize; i++)
    {
        shapes[i].Scale(scale);
    }

    for (size_t k = 0; k < textSize; k++)
    {
        text[k].Scale(scale);
    }
}

void OGLChart::Move(float x, float y)
{
    _border.Move(x, y);
    for (size_t i = 0; i < elemSize; i++)
    {
        shapes[i].Move(x, y);
    }

    for (size_t k = 0; k < textSize; k++)
    {
        text[k].Move(x, y);
    }
}


void OGLChart::Rotate(float deg)
{
    _border.Rotate(deg);
    for (size_t i = 0; i < elemSize; i++)
    {
        shapes[i].Rotate(deg);
    }

    for (size_t k = 0; k < textSize; k++)
    {
        text[k].Rotate(deg);
    }
}

void OGLChart::CenterRotate(float deg)
{
    _border.CenterRotate(deg);
    for (size_t i = 0; i < elemSize; i++)
    {
        shapes[i].CenterRotate(deg);
    }

    for (size_t k = 0; k < textSize; k++)
    {
        text[k].CenterRotate(deg);
    }
}