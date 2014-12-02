#pragma once
#include "OGLChart.h"

class OGLScatterplot3D : public OGLChart
{
public:
    OGLScatterplot3D(DataColumn col);
    OGLScatterplot3D();
    void AddDataSource(DataColumn col);
    void InitElements();
    bool MouseMove(int x, int y)
    {
        OGLChart::GetHighlight(x, y);
        return OGLChart::MouseMove(x, y);
    }
    bool MouseWheel(float deg);
protected:
    std::vector<Vec3f> store;
};