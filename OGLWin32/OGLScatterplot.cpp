#pragma once
#include "OGLScatterplot.h"

void OGLScatterPlot2D::AddDataSource(DataColumn col)
{
    if (col.Stores() == DataColumn::Storage::Categorical){ return; }
    if (data.size() == 2)
    {
        data.pop_back();
    }
    data.insert(data.begin(), col);
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

    if (data.size() < 2)
    {
        textSize = 1;
        text = new OGLText[1];
        text[0] = OGLText(Vec2f(-300, 0), Color(0, 0, 0), "Scatterplot, add " + std::to_string(2 - data.size()) + " Data Columns(Numerical) to start", "arial.glf", 18);

        return;
    }


    _border = OGLRectangle(Vec2f(-375, -250), Color(1.0, 1.0, 1.0), 500, 750);
    dataDist[new OGLLine(Vec2f(-300, -150), Color(0.0, 0.0, 0.0), Vec2f(-300, 200))] = nullptr;
    dataDist[new OGLLine(Vec2f(-300, -150), Color(0.0, 0.0, 0.0), Vec2f(300, -150))] = nullptr;

    text = new OGLText[24];
    float maxX = data[0].Max;
    float maxY = data[1].Max;
  
    for (int i = 0; i <= 10; i++)
    {
        float height = (-150) + (350 / (10))*i;
        float width = (-300) + (600 / 10)*i;
        dataDist[new OGLLine(Vec2f(-310, height), Color(0, 0, 0), Vec2f(-300, height))] = nullptr;

        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << (maxY / 10)*i;
        text[textSize] = OGLText(Vec2f(-350, height + 6), Color(0, 0, 0), ss.str(), 10);
        textSize++;

        dataDist[new OGLLine(Vec2f(width, -150), Color(0, 0, 0), Vec2f(width, -155))] = nullptr;
        std::stringstream sf;
        sf << std::fixed << std::setprecision(1) << (maxX / 10)*i;
        text[textSize] = OGLText(Vec2f(width, -155), Color(0, 0, 0), sf.str(), 10);
        textSize++;
    }


    for (int i = 0; i < data[0].size; i++)
    {
        OGLShape* index;
        float y = 0;
        float x = 0;

        if (data[0].data[i].isA<float>())
        {
            x = (600 * (data[0].data[i].asA<float>() / maxX)) - 300;
        }
        else if (data[0].data[i].isA<int>())
        {
            x = (600 * (float(data[0].data[i].asA<int>())/maxX)) - 300;
        }

        if (data[1].data[i].isA<float>())
        {
            y = (350 * (data[1].data[i].asA<float>() / maxY)) - 150;
        }
        else if (data[1].data[i].isA<int>())
        {
            y = (350 * (float(data[1].data[i].asA<int>())/maxY)) - 150;
        }


        index = new OGLRectangle(Vec2f(x, y), Color(0.f, 0.f, 0.f, 0.5f), 3,3);
        index->CenterRotate(45.0f);
		//index = new OGLCircle(Vec2f(x, y), Color(0, 0, 0), 5);
        dataDist[index] = new DataCell(std::string(data[0].Name() + " " + data[0].data[i].getString() + ":: " + data[1].Name()+ " " + data[1].data[i].getString()));
    }
    textSize+=2;
    text[22] = OGLText(Vec2f(-350, 230), Color(0, 0, 0), data[1].Name(), "arial.glf", 12);
    text[23] = OGLText(Vec2f(0, -170), Color(0, 0, 0), data[0].Name(), "arial.glf", 12);

    Scale(scale);
    Move(-_relativePos.X(), -_relativePos.Y());
    printf("Done");

}