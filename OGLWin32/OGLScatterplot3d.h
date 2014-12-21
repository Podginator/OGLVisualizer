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

	void SetUpMatrices()
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		int GLViewPort[4];
		glGetIntegerv(GL_VIEWPORT, GLViewPort);
		glFrustum((-0.5*GLViewPort[2] - xOff), (0.5*GLViewPort[2] - (xOff)), (-0.5 * GLViewPort[3] - (yOff)), (0.5 * GLViewPort[3] - (yOff)), 1.f, 500.f);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
	}

	void GetHighlightAtPoint(int x, int y, GLint* viewport);

	void RestoreMatrices()
	{
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
	}


	void ShapeMap(int x, int y, GLint* viewport);
	

	int xOff = 0;
	int yOff = 0;
};