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
    //Reset Everything
    colors = { Color("#4D4D4D"), Color("#5DA5DA"), Color("#FAA43A"), Color("#60BD68"), Color("#F17CB0"), Color("#B2912F"), Color("#B276B2"), Color("#DECF3F"), Color("#F15854") };

    //Get Distribution
    std::map<std::string, float> dist = data[0].GetDistribution();
    std::map<std::string, float>::iterator mapIt = dist.begin();
    
    if (elemSize > 0)
    {
        delete[] shapes;
        delete[] text;
    }

    //Set up Malloc for shapes (Arcs + Rectangles)
    shapes = new OGLShape[dist.size() * 2];
    //Preallocate Text area
    text = new OGLText[dist.size()];
    //Set Index

    float latestEnd = 0;
    float rectXPos = -330;
    float rectYPos = -120;
    int colIndex = 0;
    _border = OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750);

    while (mapIt != dist.end())
    {
        //Sort out Arc Segment
        float endTheta = latestEnd + (360)*mapIt->second;
        shapes[elemSize] = OGLArc(Vec2f(0, 80), colors[colIndex], latestEnd, endTheta, 150);
        latestEnd = endTheta;
        //Add Rectangle and Key 
        shapes[elemSize + 1] = OGLRectangle(Vec2f(rectXPos, rectYPos), colors[colIndex], 15*scale, 15*scale);
        text[textSize] = OGLText(Vec2f(rectXPos + 17, rectYPos + 15), Color(0, 0, 0), mapIt->first, "arial.glf", 10);
        //Darken Color for next loop and reset ColIndex
        colors[colIndex].Shade(-20);
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
            _border = OGLRectangle(Vec2f(-375, rectYPos), Color(1.0, 1.0, 1.0), 500+(-250-rectYPos), 750);
        }

        textSize++;
        elemSize += 2;
        mapIt++;
        

    }

    Scale(scale);
    Move(-_relativePos.X(), -_relativePos.Y());
    printf("Done");
}