#pragma once
#include "OGLBarChart.h"

void OGLBarChart::AddDataSource(DataColumn col)
{
    data.clear();
    data.push_back(col);
    InitElements();
}

OGLBarChart::OGLBarChart()
{
    //InitElements();
}

void OGLBarChart::InitElements()
{
    //Clear everything
    Clear();

    printf("MAX:: %d  MIN:: %d", data[0].Max, data[0].Min);

    _border = OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750);
    dataDist[new OGLLine(Vec2f(-300, -150), Color(0.0, 0.0, 0.0), Vec2f(-300, 200))] = nullptr;
    dataDist[new OGLLine(Vec2f(-300, -150), Color(0.0, 0.0, 0.0), Vec2f(300, -150))] = nullptr;

    //Get BarWidth
    float barWidth = 600 / data[0].dataDist.size();
    float maxHeight = 350;
    float dataSize = data[0].Max;
    float xLoc = -300;
    int colIndex = 0;

    float rectXPos = -320;
    float rectYPos = -200;
    text = new OGLText[data[0].dataDist.size()+11];


    printf("%d", data[0].Max);

    for (int i = 0; i <= 10; i++)
    {
        float height = (-150) + (350 / (10))*i;
        dataDist[new OGLLine(Vec2f(-310, height), colors[colIndex], Vec2f(-300, height))] = nullptr;

        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << (float(data[0].Max)/10)*i;

        text[textSize] = OGLText(Vec2f(-350, height+6), Color(0, 0, 0), ss.str(), 12);
        textSize++;
    }


    std::map<DataCell*, std::size_t>::iterator mapIt = data[0].dataDist.begin();
    while (mapIt != data[0].dataDist.end())
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