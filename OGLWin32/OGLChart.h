#include "OGLShape.h"
#include "OGLText.h"
#include "OGLData.h"

//Initial Base class where Chart will be founded. 
class OGLChart : public Listener, public Renderable
{
protected:
	//We need to define an entry point for all the charts.
	OGLShape* shapes; 
	OGLText* text;
	OGLData _data;
	size_t _elemSize;
	void RenderAxis();
	void RenderMisc();
	void RenderShapes();
	void RenderText();
	void InitElements();

public:
	OGLChart(OGLData data) : _data(data){};
	void Render();


};