#pragma once
#include "OGLSpiderChart.h"

void OGLSpiderChart::AddDataSource(DataColumn col)
{
    data.push_back(col);
    InitElements(); 
}

OGLSpiderChart::OGLSpiderChart()
{
    textSize = 1;
    text = new OGLText[1];
    text[0] = OGLText(Vec2f(-300, 0), Color(0, 0, 0), "Spiderchart, add 3 Data Columns (Numerical) to start", "arial.glf", 18);
}


bool OGLSpiderChart::MouseMove(int x, int y)
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

void OGLSpiderChart::Clear()
{
    if (dataDist.size() > 0)
    {
        delete[] text;
        textSize = 0;
        std::map<OGLShape*, DataCell*>::iterator mapIt = dataDist.begin();
        while (mapIt != dataDist.end())
        {
            delete mapIt->first;
            delete mapIt->second;
            mapIt++;
        }
        dataDist.clear();
    }
    colors = { Color("#4D4D4D", 0.55), Color("#5DA5DA", 0.55), Color("#FAA43A", 0.55), Color("#60BD68", 0.55), Color("#F17CB0", 0.55), Color("#B2912F", 0.55), Color("#B276B2", 0.55), Color("#DECF3F", 0.55), Color("#F15854", 0.55) };
}
void OGLSpiderChart::InitElements()
{
    //Clear everything
    Clear();

    if (data.size() < 3)
    {
        textSize = 1;
        text = new OGLText[1];
        text[0] = OGLText(Vec2f(-300, 0), Color(0, 0, 0), "Spiderchart, add " + std::to_string(3-data.size()) + " Data Columns(Numerical) to start", "arial.glf", 18);

        return;
    }


    text = new OGLText[data.size()];
    textSize = data.size();
    std::vector<Vec2f> VertPos = CreateSpiderVert(data.size());

    for (int i = 0; i < VertPos.size(); i++)
    {
        text[i] = OGLText(Vec2f(VertPos[i].X(), VertPos[i].Y()), Color(0, 0, 0), data[i].Name(), "arial.glf", 10);
    }

    dataDist[new OGLShape(Vec2f(0, 0), Color(0.0, 0.0, 0.0), data.size(), GL_LINE_LOOP, VertPos)] = nullptr;


    int max = 0;
    //Get Max.
    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < data.size(); k++)
        {
            if (data[k].rawData[i].isA<float>())
            {
                max = data[k].rawData[i].asA<float>() > max ? data[k].rawData[i].asA<float>() : max;
            }
            else if (data[k].rawData[i].isA<int>())
            {
                max = data[k].rawData[i].asA<int>() > max ? data[k].rawData[i].asA<int>() : max;
            }
            
        }
    }

    for (int i = 0; i < 3; i++)
    {
        std::vector<Vec2f> newVert = std::vector<Vec2f>(VertPos.size());
        for (int k = 0; k < data.size(); k++)
        {
            if (data[k].rawData[i].isA<float>())
            {
                newVert[k] = VertPos[k] * ( data[k].rawData[i].asA<float>() / max);
                dataDist[new OGLCircle(Vec2f(newVert[k].X(), newVert[k].Y()), Color(0, 0, 0), 2.5)] = new DataCell(std::string("Data " + std::to_string(i) + "::- " + data[k].Name() + " " + std::to_string(data[k].rawData[i].asA<float>())));

            }
            else if (data[k].rawData[i].isA<int>())
            {
                newVert[k] = VertPos[k] * (float(data[k].rawData[i].asA<int>())/max);
                dataDist[new OGLCircle(Vec2f(newVert[k].X(), newVert[k].Y()), Color(0, 0, 0), 2.5)] = new DataCell(std::string("Data " + std::to_string(i) + "::- " + data[k].Name()+" "+std::to_string(data[k].rawData[i].asA<int>())));
            }
            
        }
        dataDist[new OGLShape(Vec2f(0, 0), colors[i], data.size(), GL_POLYGON, newVert)] = nullptr;
    }


    _border = OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750);
    Scale(scale);
    Move(-_relativePos.X(), -_relativePos.Y());
    printf("Done");

} 

std::vector<Vec2f> OGLSpiderChart::CreateSpiderVert(int size)
{
    std::vector<Vec2f> res;

    for (int i = 0; i < size; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(size);

        float x = 200 * cosf(theta);
        float y = 200 * sinf(theta);
        
        res.push_back(Vec2f(x, y));
    }


    return res;

}