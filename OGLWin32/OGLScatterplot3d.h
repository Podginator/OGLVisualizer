#pragma once
#include "OGLChart.h"
#include "OGLRectangle3D.h"

class OGLScatterplot3D : public OGLChart
{
public:
	OGLScatterplot3D(DataColumn col);
	OGLScatterplot3D();
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
	float xRot = 0.00f;
	float yRot = 0.f;
};