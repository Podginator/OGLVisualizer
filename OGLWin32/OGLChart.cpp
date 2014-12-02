#pragma once
#include "OGLChart.h"
#include <typeinfo>

OGLChart::OGLChart() : _border(OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750))
{
    textSize = 0;
    highlightText = nullptr;
    colors = { Color("#4D4D4D"), Color("#5DA5DA"), Color("#FAA43A"), Color("#60BD68"), Color("#F17CB0"), Color("#B2912F"), Color("#B276B2"), Color("#DECF3F"), Color("#F15854") };
}

DataColumn* OGLChart::FindDataCol(DataCell* cell)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data[i].dataDist.count(cell) > 0)
        {
            return &data[i];
        }
    }

    return nullptr;
}

void OGLChart::Clear()
{
    colors = { Color("#4D4D4D"), Color("#5DA5DA"), Color("#FAA43A"), Color("#60BD68"), Color("#F17CB0"), Color("#B2912F"), Color("#B276B2"), Color("#DECF3F"), Color("#F15854") };

    if (dataDist.size() > 0 || textSize>0)
    {
        delete[] text;
        //delete[] text;
        textSize = 0;
        std::map<OGLShape*, DataCell*>::iterator mapIt = dataDist.begin();
        while (mapIt != dataDist.end())
        {
            delete mapIt->first;
            //delete mapIt->second;
            mapIt++;
        }
        dataDist.clear();
    }
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
    
    if (!(Listener::keys[16]))
    {
        _border.Scale(scale);
    }
    
    std::map<OGLShape*, DataCell*>::iterator mapIt = dataDist.begin();

    while (mapIt != dataDist.end())
    {
        OGLShape* shape = mapIt->first;
        if (dynamic_cast<OGLShape3D*>(shape) && Listener::keys[16])
        {
            shape->Scale(scale);
        }
        if (!(Listener::keys[16]))
        {
            mapIt->first->Scale(scale);
        }
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

std::tuple<bool, DataCell*, DataColumn*> OGLChart::MouseRB(int x, int y)
{
    if (!(_border.MouseInside(x, y))){ return std::make_tuple(false, nullptr, nullptr); }

    std::map<OGLShape*, DataCell*>::iterator mapIt = dataDist.begin();
    while (mapIt != dataDist.end())
    {
        if (mapIt->first->MouseInside(x, y))
        {
            //printf("Yes");
            if (mapIt->second != nullptr)
            {
                return std::make_tuple(true, mapIt->second, FindDataCol(mapIt->second));
            }
        }
        mapIt++;
    }
    return std::make_tuple(true, nullptr, nullptr);
}

void OGLChart::GetDistHighlight(int x, int y)
{
    if (highlightText){ delete highlightText; }
    std::map<OGLShape*, DataCell*>::iterator mapIt = dataDist.begin();
    while (mapIt != dataDist.end())
    {
        if (mapIt->first->MouseInside(x, y))
        {
            if (mapIt->second != nullptr)
            {
                float percent = ((FindDataCol(mapIt->second)->operator[](mapIt->second) / float(data[0].size)) * 100);
                highlightText = new OGLText(Vec2f(x + 5, y), Color(0.25f, 0.25f, 0.25f), mapIt->second->getString() + ":- " + std::to_string(data[0][mapIt->second]) + "(" + std::to_string(percent) + "%)", "arial.glf", 16);
                break;
            }

        }
        mapIt++;
        highlightText = nullptr;
    }
}
void OGLChart::GetHighlight(int x, int y)
{
    if (highlightText){ delete highlightText; }
    std::map<OGLShape*, DataCell*>::iterator mapIt = dataDist.begin();
    while (mapIt != dataDist.end())
    {
        if (mapIt->first->MouseInside(x, y))
        {
            if (mapIt->second != nullptr)
            {
                highlightText = new OGLText(Vec2f(x + 5, y), Color(0.25f, 0.25f, 0.25f), mapIt->second->getString(), "arial.glf", 16);
                break;
            }

        }
        mapIt++;
        highlightText = nullptr;
    }

}


bool OGLChart::MouseMove(int x, int y)
{
    if (MouseDown&_border.MouseInside(x, y))
    {
        float displaceX = x - Listener::x;
        float displaceY = y - Listener::y;
        _relativePos -= Vec2f(displaceX, displaceY);
        Move(displaceX, displaceY);
    }
    Listener::x = float(x);
    Listener::y = float(y);
    return true;
}
bool OGLChart::MouseLBDown(int x, int y)
{
    MouseDown = true;
    Listener::x = float(x);
    Listener::y = float(y);
    return _border.MouseInside(x, y);
}
bool OGLChart::MouseLBUp(int x, int y)
{
    MouseDown = false;
    return true;
}
bool OGLChart::MouseWheel(float deg)
{
    if (Listener::keys[17])
    {
        static float opacity = 1.f;
        if (deg > 0)
        {
            opacity = opacity < 1.f ? opacity + 0.1 : 1.f;
        }
        else
        {
            opacity = opacity > 0.1f ? opacity - 0.1 : 0.1f;
        }
        SetOpacity(opacity);
    }
    else
    {
        if (deg > 0)
        {
            Scale(1.1f);
            scale *= 1.1f;
        }
        else
        {
            Scale(0.9f);
            scale *= 0.9f;
        }
    }

    return true;
}