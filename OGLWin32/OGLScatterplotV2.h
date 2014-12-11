//Version of the Scatterplot where full 3d Motion is enabled.
//Kept both versions because I kind of liked the interactions with the old versions, but it didn't have full 6 degrees of motion that this one does.
//Z+X and the scroll wheen is to adjust the x and y Positions, rotating them around the axis. 

#pragma once
#include "OGLChart.h"
#include "OGLRectangle3D.h"
#include "OGLWindow.h"

class OGLScatterplot3DV2 : public OGLChart
{
public:
	OGLScatterplot3DV2(DataColumn col);
	OGLScatterplot3DV2();
	void AddDataSource(DataColumn col);
	void InitElements();
	void Move(float x, float y);
	void Render();
	bool MouseMove(int x, int y)
	{
		int Mousex = x - xOff;
		int Mousey = y - yOff;
		if (MouseDown&_border.MouseInside(Mousex, Mousey))
		{
			float displaceX = x - Listener::x;
			float displaceY = y - Listener::y;
			Move(displaceX, displaceY);
		}
		Listener::x = float(x);
		Listener::y = float(y);
		return true;
	}
	bool MouseWheel(float deg);
	bool MouseLBDown(int x, int y);
protected:
	int xOff = 0;
	int yOff = 0;
	float xRot = 0.0f;
	float yRot = 0.0f;
};