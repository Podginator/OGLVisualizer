#pragma once
#include "OGLPieChart.h"

OGLPieChart::OGLPieChart(DataColumn* col)
{
    OGLChart::AddDataSource(col);
    colors = { Color("#4D4D4D"), Color("#5DA5DA"), Color("#FAA43A"), Color("#60BD68"), Color("#F17CB0"), Color("#B2912F"), Color("#B276B2"), Color("#DECF3F"), Color("#F15854") };
    InitElements();
    
}

void OGLPieChart::AddDataSource(DataColumn* col)
{
    data.clear();
    data.push_back(col);
    InitElements();
}

void OGLPieChart::InitElements()
{
    std::map<std::string, float> dist = data[0]->GetDistribution();
    std::map<std::string, float>::iterator mapIt = dist.begin();

    shapes = new OGLShape[dist.size() * 2];
    text = new OGLText[dist.size()];
    size_t i = 0;
    float latestEnd = 0;
    float rectPos = 180;
    int colIndex = 0;
    int textIndex = 0;
    while (mapIt != dist.end())
    {
        float endTheta = latestEnd + (360)*mapIt->second;
        shapes[i] = OGLArc(Vec2f(0, 0), colors[colIndex], latestEnd, endTheta, 150);
        shapes[i + 1] = OGLRectangle(Vec2f(240, rectPos), colors[colIndex], 15, 15);
        colors[colIndex].Shade(-20);
        text[textIndex] = OGLText(Vec2f(250, rectPos - 7.5), Color(0, 0, 0), mapIt->first.c_str(), "arial.glf", 12);
        colIndex = colIndex == 8 ? 0 : colIndex + 1;
        latestEnd = endTheta;
        i += 2;
        textIndex++;
        rectPos -= 15;
        _elemSize += 2;
        mapIt++;
    }
}