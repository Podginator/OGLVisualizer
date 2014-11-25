#pragma once
#include "OGLScatterplot.h"

void OGLScatterPlot2D::AddDataSource(DataColumn col)
{
    data.push_back(col);
    InitElements();
}

OGLScatterPlot2D::OGLScatterPlot2D()
{
    textSize = 1;
    text = new OGLText[1];
    text[0] = OGLText(Vec2f(-300, 0), Color(0, 0, 0), "Scatterplot, add 2 Data Columns (Numerical) to start", "arial.glf", 18);
}

void OGLScatterPlot2D::InitElements()
{
    //Clear everything
    Clear();

    _border = OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750);
    dataDist[new OGLLine(Vec2f(-300, -150), Color(0.0, 0.0, 0.0), Vec2f(-300, 200))] = nullptr;
    dataDist[new OGLLine(Vec2f(-300, -150), Color(0.0, 0.0, 0.0), Vec2f(300, -150))] = nullptr;


    Scale(scale);
    Move(-_relativePos.X(), -_relativePos.Y());
    printf("Done");

}