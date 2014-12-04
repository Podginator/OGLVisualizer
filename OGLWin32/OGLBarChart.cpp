#pragma once
#include "OGLBarChart.h"

void OGLBarChart::AddDataSource(DataColumn col)
{
    data.clear();
    data.push_back(col);
    dist = col.GetDistribution();
    InitElements();
}

OGLBarChart::OGLBarChart()
{
    
}

size_t OGLBarChart::MaxDist()
{
    size_t max = 0;
    std::map<DataCell*, std::size_t>::iterator mapIt = dist.begin();
    while (mapIt != dist.end())
    {
        max = mapIt->second > max ? mapIt->second : max;
        mapIt++;
    }

    return max;
}

void OGLBarChart::InitElements()
{
    //Clear everything
    Clear();
    std::map<DataCell*, std::size_t>::iterator map = dist.begin();
    while (map != dist.end())
    {
        printf(map->first->getString().c_str());
        printf("%d\n", map->second);
        map++;
    }

    _border = OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750);
    dataDist[new OGLLine(Vec2f(-300, -150), Color(0.0, 0.0, 0.0), Vec2f(-300, 200))] = nullptr;
    dataDist[new OGLLine(Vec2f(-300, -150), Color(0.0, 0.0, 0.0), Vec2f(300, -150))] = nullptr;

    //Get BarWidth
    float barWidth = 600 / dist.size();
    float maxHeight = 350;
    float dataSize = MaxDist();
    float xLoc = -300;
    int colIndex = 0;

    float rectXPos = -320;
    float rectYPos = -200;
    text = new OGLText[dist.size()+11];


    for (int i = 0; i <= 10; i++)
    {
        float height = (-150) + (350 / (10))*i;
        dataDist[new OGLLine(Vec2f(-310, height), colors[colIndex], Vec2f(-300, height))] = nullptr;

        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << (float(dataSize)/10)*i;

        text[textSize] = OGLText(Vec2f(-350, height+6), Color(0, 0, 0), ss.str(), 12);
        textSize++;
        text[textSize] = OGLText(Vec2f(-350, height + 6), Color(0, 0, 0), ss.str(), 12);
    }


    std::map<DataCell*, std::size_t>::iterator mapIt = dist.begin();
    while (mapIt != dist.end())
    {
        float percent = mapIt->second / dataSize;
        float height = maxHeight * percent;
        OGLShape* index = new OGLRectangle(Vec2f(xLoc, -150), colors[colIndex], height, barWidth);
        xLoc += barWidth;
        dataDist[index] = mapIt->first;

        index = new OGLRectangle(Vec2f(rectXPos, rectYPos), colors[colIndex], 15, 15);
        dataDist[index] = nullptr;
        text[textSize] = OGLText(Vec2f(rectXPos + 17, rectYPos + 15), Color(0, 0, 0), mapIt->first->getString(), "arial.glf", 10);

        colors[colIndex].Shade(-10.f);
        colIndex = colIndex == 8 ? 0 : colIndex + 1;

        rectXPos += 15 + text[textSize]._width + 20;
        if (rectXPos > (320))
        {
            rectXPos = -320;
            rectYPos -= 20;
        }

        if (rectYPos < -250)
        {
            _border = OGLRectangle(Vec2f(-375, rectYPos), Color(1.0, 1.0, 1.0), 500 + (-250 - rectYPos), 750);
        }

        textSize++;
        mapIt++;
    }

    Scale(scale);
    Move(-_relativePos.X(), -_relativePos.Y());
    printf("Done");
    
}

void OGLBarChart::GetHighlight(int x, int y)
{
    if (highlightText){ delete highlightText; }
    std::map<OGLShape*, DataCell*>::iterator mapIt = dataDist.begin();
    while (mapIt != dataDist.end())
    {
        if (mapIt->first->MouseInside(x, y))
        {
            if (mapIt->second != nullptr)
            {
                float percent = (dist[mapIt->second]/ float(data[0].size) * 100);
                highlightText = new OGLText(Vec2f(x + 5, y), Color(0.25f, 0.25f, 0.25f), mapIt->second->getString() + ":- " + std::to_string(dist[mapIt->second]) + "(" + std::to_string(percent) + "%)", "arial.glf", 16);
                break;
            }

        }
        mapIt++;
        highlightText = nullptr;
    }
}