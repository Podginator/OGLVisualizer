#pragma once
#include "OGLChart.h"

class OGLPieChart : public OGLChart
{
public:
    OGLPieChart(DataColumn* col)
    {
        OGLChart::AddDataSource(col);
        InitElements();
    }

    void AddDataSource(DataColumn* col)
    {
        data.clear();
        data.push_back(col);
        InitElements();
    }

    void InitElements()
    {
        std::map<std::string, float> dist = data[0]->GetDistribution();
        std::map<std::string, float>::iterator mapIt = dist.begin();

        shapes = new OGLShape[dist.size()];
        size_t i = 0;
        Color col(0.3, 0.3, 0.3);
        float latestEnd = 0;
        float total = 0;
        while (mapIt != dist.end())
        {
            float endTheta = latestEnd + (360)*mapIt->second;
            shapes[i] = OGLArc(Vec2f(0, 0), col, latestEnd, (endTheta-latestEnd), 150);
            latestEnd = endTheta;
            i++;
            _elemSize++;
            mapIt++;
            col.red = col.red * 1.02;
            col.blue = col.blue * 1.02;
            col.green = col.green * 1.02;
        }

        printf("%f", latestEnd);
    }

    void Render()
    {
        OGLChart::Render();
    }

    bool MouseMove(int x, int y)
    {
        return true;
    }
    bool MouseLBDown(int x, int y)
    {
        return true;
    }
    bool MouseLBUp(int x, int y)
    {
        return true;
    };
};