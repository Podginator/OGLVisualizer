#pragma once
#include "OGLChart.h"

OGLChart::OGLChart() : _border(OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750))
{
    textSize = 0;
    elemSize = 0;
    highlightText = nullptr;
}

void OGLChart::Render()
{
    _border.Render();

    std::map<OGLShape*, DataCell*>::iterator mapIt = dataDist.begin();

    while (mapIt != dataDist.end())
    {
        mapIt->first->Render();
        mapIt++;
    }

    for (size_t k = 0; k < textSize; k++)
    {
        text[k].Render();
    }

    if (highlightText)
    {
        highlightText->Render();
    }

}

void OGLChart::Scale(float scale)
{


    _border.Scale(scale);
    
    std::map<OGLShape*, DataCell*>::iterator mapIt = dataDist.begin();

    while (mapIt != dataDist.end())
    {
        mapIt->first->Scale(scale);
        mapIt++;
    }
    for (size_t k = 0; k < textSize; k++)
    {
        text[k].Scale(scale);
    }
}

void OGLChart::Move(float x, float y)
{
    _border.Move(x, y);


    std::map<OGLShape*, DataCell*>::iterator mapIt = dataDist.begin();

    while (mapIt != dataDist.end())
    {
        mapIt->first->Move(x, y);
        mapIt++;
    }


    for (size_t k = 0; k < textSize; k++)
    {
        text[k].Move(x, y);
    }
}


void OGLChart::Rotate(float deg)
{
    _border.Rotate(deg);

    for (size_t k = 0; k < textSize; k++)
    {
        text[k].Rotate(deg);
    }
}

void OGLChart::CenterRotate(float deg)
{
    _border.CenterRotate(deg);
    for (size_t k = 0; k < textSize; k++)
    {
        text[k].CenterRotate(deg);
    }
}