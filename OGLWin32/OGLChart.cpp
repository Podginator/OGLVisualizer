#pragma once
#include "OGLChart.h"

OGLChart::OGLChart() : _border(OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750))
{
    textSize = 0;
    highlightText = nullptr;
    colors = { Color("#4D4D4D"), Color("#5DA5DA"), Color("#FAA43A"), Color("#60BD68"), Color("#F17CB0"), Color("#B2912F"), Color("#B276B2"), Color("#DECF3F"), Color("#F15854") };
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

void OGLChart::SetOpacity(float n)
{


    _border.SetOpacity(n);

    std::map<OGLShape*, DataCell*>::iterator mapIt = dataDist.begin();

    while (mapIt != dataDist.end())
    {
        mapIt->first->SetOpacity(n);
        mapIt++;
    }
    for (size_t k = 0; k < textSize; k++)
    {
        text[k].SetOpacity(n);
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