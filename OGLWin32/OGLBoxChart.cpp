#pragma once
#include "OGLBoxChart.h"

void OGLBoxChart::AddDataSource(DataColumn col)
{
    data.clear();
    data.push_back(col);
    InitElements();
}

OGLBoxChart::OGLBoxChart()
{
    textSize = 1;
    text = new OGLText[1];
    text[0] = OGLText(Vec2f(-300, 0), Color(0, 0, 0), "Box Chart, add a Data Column (Numerical) to start", "arial.glf", 18);
}

void OGLBoxChart::InitElements()
{
    //First we have to clear everything.
    Clear();

    //Set up indices and reset _Border size. Perhaps not necessary for this.
    dataDist[new OGLLine(Vec2f(-300, -150), Color(0.0, 0.0, 0.0), Vec2f(300, -150))] = nullptr;
    float maxWidth = 600;
    float Maxsize = data[0].Max;
    float MinSize = data[0].Min;
    float MedSize = GetMedian();
    std::tuple<float, float> Quartile = GetQuartiles();
    float LowerSize = std::get<1>(Quartile);
    float UpperSize= std::get<0>(Quartile);

    text = new OGLText[20];

    for (int i = 0; i <= 10; i++)
    {
        float width = (-300) + (600 / 10)*i;

        dataDist[new OGLLine(Vec2f(width, -150), Color(0, 0, 0), Vec2f(width, -155))] = nullptr;
        std::stringstream sf;
        sf << std::fixed << std::setprecision(1) << (Maxsize / 10)*i;
        text[textSize] = OGLText(Vec2f(width, -155), Color(0, 0, 0), sf.str(), 10);
        textSize++;
    }

    float MinVal = 0;
    float MedVal = -300 + 600 * (MedSize / Maxsize);
    float LowVal = -300 + 600 * (LowerSize / Maxsize);
    float UpVal = -300 + 600 * (UpperSize / Maxsize);
    if (MinSize != 0.0f)
    {
        MinVal = -300 + 600*(MinSize / Maxsize);
    }
    

    dataDist[new OGLLine(Vec2f(MinVal, -70), Color(0, 0, 0), Vec2f(300, -70))] = nullptr;
    dataDist[new OGLRectangle(Vec2f(MinVal, -90), Color(0, 0, 0), 40, 2)] = new DataCell(std::string("MinVal = ") + std::to_string(MinSize));
    dataDist[new OGLRectangle(Vec2f(300, -90), Color(0, 0, 0), 40, 2)] =  new DataCell(std::string("MaxVal = ") + std::to_string(Maxsize));
    dataDist[new OGLRectangle(Vec2f(LowVal, -90), Color(1,0,0,0.5), 40, UpVal - LowVal)] = new DataCell(std::string("Quartile = " + std::to_string(LowerSize) + " to " + std::to_string(UpperSize)));
    dataDist[new OGLRectangle(Vec2f(MedVal, -90), Color(0, 0, 0), 40, 2)] = new DataCell(std::string("MedVal = ") + std::to_string(MedSize));
}

bool sortDataCell(DataCell& i, DataCell& j)
{
    float val1;
    float val2;

    if (i.isNull() || j.isNull()){ return true; }

    if (i.isA<float>())
    {
        val1 = i.asA<float>();
    }
    else if (i.isA<int>())
    {
        val1 = float(i.asA<int>());
    }

    if (j.isA<float>())
    {
        val2 = j.asA<float>();
    }
    else if (j.isA<int>())
    {
        val2 = float(j.asA<int>());
    }
    return val1 > val2;
}

float OGLBoxChart::GetMedian()
{
    float res;
    std::sort(data[0].data.begin(), data[0].data.begin()+ data[0].size, sortDataCell);

    int index = data[0].data.size()/2;

    if (data[0].data[index].isA<float>())
    {
        res = data[0].data[index].asA<float>();
    }
    else
    {
        res = data[0].data[index].asA<int>();
    }


    return res;
}

std::tuple<float, float> OGLBoxChart::GetQuartiles()
{
    int mid = data[0].data.size() / 2;
    float lowerQuartile;
    float upperQuartile;


    float midlq = mid / 2;
    if (mid % 2 == 0)
    {
        if (data[0].data[midlq].isA<float>())
        {
            lowerQuartile = (data[0].data[midlq].asA<float>() + data[0].data[midlq - 1].asA<float>())/2;
        }
        else
        {
            lowerQuartile = (data[0].data[midlq].asA<int>() + data[0].data[midlq - 1].asA<int>()) / 2;
        }
    }
    else
    {
        if (data[0].data[midlq].isA<float>())
        {
            lowerQuartile = data[0].data[midlq].asA<float>();
        }
        else
        {
            lowerQuartile = data[0].data[midlq].asA<int>();
        }
    }

    float miduq = data[0].data.size() - midlq;

    if (mid % 2 == 0)
    {
        if (data[0].data[midlq].isA<float>())
        {
            upperQuartile = (data[0].data[miduq].asA<float>() + data[0].data[miduq - 1].asA<float>()) / 2;
        }
        else
        {
            upperQuartile = (data[0].data[miduq].asA<int>() + data[0].data[miduq - 1].asA<int>()) / 2;
        }
    }
    else
    {
        if (data[0].data[midlq].isA<float>())
        {
            upperQuartile = data[0].data[miduq].asA<float>();
        }
        else
        {
            upperQuartile = data[0].data[miduq].asA<int>();
        }
    }

    
    return std::make_tuple(lowerQuartile, upperQuartile);

}

