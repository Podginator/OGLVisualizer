#pragma once
#include "OGLPieChart.h"

OGLPieChart::OGLPieChart(DataColumn col)
{
    AddDataSource(col);
}

OGLPieChart::OGLPieChart()
{
    textSize = 1;
    text = new OGLText[1];
    text[0] = OGLText(Vec2f(-300, 0), Color(0, 0, 0), "PieChart, add a Data Columns (Categorical) to start", "arial.glf", 18);
}

void OGLPieChart::AddDataSource(DataColumn col)
{
    data.clear();
    data.push_back(col);
    InitElements();
}

void OGLPieChart::InitElements()
{
    Clear();
    text = new OGLText[data[0].dataDist.size()+1];

    float dataSize = data[0].size;
    float latestEnd = 0;
    float rectXPos = -330;
    float rectYPos = -120;
    int colIndex = 0;
    _border = OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750);

    std::map<DataCell*, std:: size_t>::iterator mapIt = data[0].dataDist.begin();
    while (mapIt != data[0].dataDist.end())
    {
        
        float percent = mapIt->second / dataSize;
        float endTheta = latestEnd + (360)*percent;
        OGLShape* index = new OGLArc(Vec2f(0, 80), colors[colIndex], latestEnd, endTheta, 150);
        latestEnd = endTheta;
        dataDist[index] = mapIt->first;

        index = new OGLRectangle(Vec2f(rectXPos, rectYPos), colors[colIndex], 15, 15);
        dataDist[index] = nullptr;
        text[textSize] = OGLText(Vec2f(rectXPos + 17, rectYPos + 15), Color(0, 0, 0), mapIt->first->getString(), "arial.glf", 10);
        rectXPos += 15 + text[textSize]._width + 20;
        if (rectXPos > (320))
        {
            rectXPos = -330;
            rectYPos -= 20;
        }

        if (rectYPos < -250)
        {
            _border = OGLRectangle(Vec2f(-375, rectYPos), Color(1.0, 1.0, 1.0), 500 + (-250 - rectYPos), 750);
        }

        colors[colIndex].Shade(-10.f);
        colIndex = colIndex == 8 ? 0 : colIndex + 1;
        //Set the rectangle to be 35 + Necessary Text Distance away.

        textSize++;
        mapIt++;

    }

    Scale(scale);
    Move(-_relativePos.X(), -_relativePos.Y());
    printf("Done");
}