//Version of the Scatterplot where full 3d Motion is enabled.
//Kept both versions because I kind of liked the interactions with the old versions, but it didn't have full 6 degrees of motion that this one does.
//Z+X and the scroll wheen is to adjust the x and y Positions, rotating them around the axis. 

#pragma once
#include "OGLChart.h"
#include "OGLScatterplot3d.h"
#include "OGLRectangle3D.h"
class OGLScatterplot3DV2 : public OGLScatterplot3D
{
public:
	OGLScatterplot3DV2(DataColumn col);
	OGLScatterplot3DV2();
	void AddDataSource(DataColumn col);
	void InitElements();
	void Render();
	bool MouseWheel(float deg);
protected:
	int xOff = 0;
	int yOff = 0;
	float xRot = 0.0f;
	float yRot = 0.0f;
	void GetHighlightAtPoint(int x, int y, GLint* viewport);
};