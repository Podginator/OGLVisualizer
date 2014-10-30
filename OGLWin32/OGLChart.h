#include "OGLShape.h"
#include "OGLText.h"
#include "OGLData.h"
#include "OGLRectangle.h"
#include "OGLArc.h"
#include "OGLLine.h"
#include "OGLCircle.h"

//Initial Base class where Chart will be founded. 
class OGLChart : public Listener, public Renderable
{
protected:
    //We need to define an entry point for all the charts.
    OGLShape* shapes; 
    OGLText* text;
    OGLRectangle _border;
    std::vector<CSVColumn> data;
    size_t _elemSize;
    void RenderAxis();
    void RenderMisc();
    void RenderShapes();
    void RenderText();
    void InitElements();

public:
    template<typename... Args>
    OGLChart(Args const&... args) :data{args...}{}

    void Render();

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