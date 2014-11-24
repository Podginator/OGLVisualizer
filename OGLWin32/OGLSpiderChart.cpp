#pragma once
#include "OGLSpiderChart.h"

void OGLSpiderChart::AddDataSource(DataColumn col)
{
    data.clear();
    data.push_back(col);
    InitElements();
}

OGLSpiderChart::OGLSpiderChart()
{
}


void OGLSpiderChart::InitElements()
{
    //Clear everything
    Clear();

    _border = OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750);

    std::vector<Vec2f> VertPos = CreateSpiderVert();
    dataDist[new OGLShape(Vec2f(0, 0), Color(0.0, 0.0, 0.0), data[0].dataDist.size(), GL_LINE_LOOP, VertPos)] = nullptr;
    std::map<DataCell*, std::size_t>::iterator mapIt = data[0].dataDist.begin();
    size_t index = 0;
    while (mapIt != data[0].dataDist.end())
    {
        float size = float(mapIt->second)/data[0].Max;
        printf("%f\n", size);
        VertPos[index] = VertPos[index] * size;
        mapIt++;
        index++;
    }

    dataDist[new OGLShape(Vec2f(0, 0), colors[1], data[0].dataDist.size(), GL_TRIANGLE_FAN, VertPos)] = nullptr;

    Scale(scale);
    Move(-_relativePos.X(), -_relativePos.Y());
    printf("Done");

} 

std::vector<Vec2f> OGLSpiderChart::CreateSpiderVert()
{
    std::vector<Vec2f> res;

    int SecSize = data[0].dataDist.size();

    for (int i = 0; i < SecSize; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(SecSize);//get the current angle 

        float x = 150 * cosf(theta);//calculate the x component 
        float y = 150 * sinf(theta);//calculate the y component 
        
        res.push_back(Vec2f(x, y));
    }


    return res;

}