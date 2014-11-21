#pragma once

#include "KeyboardHelper.h"
#include "OGLShape.h"
#include "OGLText.h"
#include "OGLRectangle.h"
#include "OGLArc.h"
#include "OGLLine.h"
#include "OGLCircle.h"
#include "DataColumn.h"
#include <vector>
#include <tuple>
#include <array>

//Initial Base class where Chart will be founded. 
class OGLChart : public Listener, public Renderable
{
protected:
    std::array<Color, 9> colors;
    //We need to define an entry point for all the charts.
    std::map<OGLShape*, DataCell*> dataDist;
    OGLText* text;
    OGLText* highlightText;
    OGLRectangle _border;
    std::vector<DataColumn> data;
    Vec2f _relativePos = Vec2f(0, 0);
    //void InitElements();
    size_t textSize;

    DataColumn* FindDataCol(DataCell* cell)
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

   
    bool MouseInside(int x, int y){ return true; }

public:
    OGLChart();
    virtual void InitElements() = 0;
    virtual void Render();
    virtual void AddDataSource(DataColumn _data){ data.push_back(_data); }

    void CenterRotate(float deg);
    void Rotate(float deg);
    void Scale(float scale);
    void Move(float x, float y);
    void SetOpacity(float n);

    std::tuple<bool, DataCell*, DataColumn*> MouseRB(int x, int y)
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

    bool MouseMove(int x, int y)
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
                    highlightText = new OGLText(Vec2f(x + 5, y), Color(0, 0, 0), mapIt->second->getString() + ":- " + std::to_string(data[0][mapIt->second]) + "(" + std::to_string(percent) + "%)", "arial.glf",16);
                }
                break; 
            }
            mapIt++;
            highlightText = nullptr;
        }

        if (MouseDown&_border.MouseInside(x,y))
        {
            float displaceX = x - Listener::x ;
            float displaceY = y - Listener::y;
            _relativePos -= Vec2f(displaceX, displaceY);
            Move(displaceX, displaceY);
        }
        Listener::x = float(x);
        Listener::y = float(y);
        return true;
    }
    bool MouseLBDown(int x, int y)
    {   
        MouseDown = true;
        Listener::x = float(x);
        Listener::y = float(y);
        return _border.MouseInside(x,y);
    }
    bool MouseLBUp(int x, int y)
    {
        MouseDown = false;
        return true;
    };

    bool MouseWheel(float deg)
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


};