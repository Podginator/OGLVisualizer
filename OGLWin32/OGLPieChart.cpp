#pragma once
#include "OGLPieChart.h"

OGLPieChart::OGLPieChart(DataColumn col)
{
    AddDataSource(col);
}

OGLPieChart::OGLPieChart()
{

}

void OGLPieChart::AddDataSource(DataColumn col)
{
    data.clear();
    data.push_back(col);
    InitElements();
}

void OGLPieChart::InitElements()
{
    //Reset Colors
    colors = { Color("#4D4D4D"), Color("#5DA5DA"), Color("#FAA43A"), Color("#60BD68"), Color("#F17CB0"), Color("#B2912F"), Color("#B276B2"), Color("#DECF3F"), Color("#F15854") };

    //Get Distribution
    
    
    if (dataDist.size() > 0)
    {
        delete[] text;
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

    //Set up Malloc for shapes (Arcs + Rectangles)
    //Preallocate Text area
    text = new OGLText[data[0].dataDist.size()];
    //Set Index

    float latestEnd = 0;
    float rectXPos = -330;
    float rectYPos = -120;
    int colIndex = 0;
    _border = OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750);



    std::map<DataCell*, std:: size_t>::iterator mapIt = data[0].dataDist.begin();

    while (mapIt != data[0].dataDist.end())
    {
        float datasize = data[0].size;
        float percent = mapIt->second / datasize;
        float endTheta = latestEnd + (360)*percent;
        OGLShape* index = new OGLArc(Vec2f(0, 80), colors[colIndex], latestEnd, endTheta, 150);
        latestEnd = endTheta;
        dataDist[index] = mapIt->first;

        index = new OGLRectangle(Vec2f(rectXPos, rectYPos), colors[colIndex], 15 * scale, 15 * scale);
        dataDist[index] = nullptr;
        text[textSize] = OGLText(Vec2f(rectXPos + 17, rectYPos + 15), Color(0, 0, 0), mapIt->first->getString(), "arial.glf", 10);
        
        colors[colIndex].Shade(-10.f);
        colIndex = colIndex == 8 ? 0 : colIndex + 1;
        //Set the rectangle to be 35 + Necessary Text Distance away.
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

        textSize++;
        mapIt++;

    }

    Scale(scale);
    Move(-_relativePos.X(), -_relativePos.Y());
    printf("Done");
}