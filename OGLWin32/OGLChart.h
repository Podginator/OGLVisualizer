#pragma once
#include "OGLShape.h"
#include "OGLText.h"
#include "OGLRectangle.h"
#include "OGLArc.h"
#include "OGLLine.h"
#include "OGLCircle.h"
#include "DataColumn.h"
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <tuple>
#include <array>

//Initial Base class where Chart will be founded. 
class OGLChart : public Listener, public Renderable
{
protected:
    std::array<Color, 9> colors;
    //We need to define an entry point for all the charts.
    std::map<OGLShape*, DataCell*> dataDist;
    OGLText* text;
    OGLText* highlightText;
    OGLRectangle _border;
    std::vector<DataColumn> data;
    Vec2f _relativePos = Vec2f(0, 0);
    //void InitElements();
    size_t textSize;

    DataColumn* FindDataCol(DataCell* cell);
    void Clear();
    virtual bool MouseInside(int x, int y){ return true; }
    void GetDistHighlight(int x, int y);
    void GetHighlight(int x, int y);


public:
    OGLChart();
    virtual void InitElements() = 0;
    virtual void Render();
    virtual void AddDataSource(DataColumn _data){ data.push_back(_data); }

    void CenterRotate(float deg);
    void Rotate(float deg);
    void Scale(float scale);
    void Move(float x, float y);
    void SetOpacity(float n);
    std::tuple<bool, DataCell*, DataColumn*> MouseRB(int x, int y);

    bool MouseMove(int x, int y);
    bool MouseLBDown(int x, int y);
    bool MouseLBUp(int x, int y);
    bool MouseWheel(float deg);


};