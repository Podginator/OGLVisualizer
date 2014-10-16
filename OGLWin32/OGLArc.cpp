#pragma once

#include "OGLArc.h"


OGLArc::OGLArc(Vec2 position, Color color, float startTheta, float endTheta, float radius)
:OGLShape(position, color, endTheta+3)
{
	_startTheta = startTheta;
	_endTheta = endTheta;
	_radius = radius;
	CreateArc();
}

void OGLArc::CreateArc()
{
	int i;
	vertexs[0] = _position;
	vertexs[1] = Vec2(_position.X(), _position.Y() + _radius);
	for (i = 0; i <= _endTheta; i++)
	{
		printf("%d\n", i);
		vertexs[2+i] = MathHelper<float>::Matrix2Dtransform(-(float)i) * vertexs[1];
	}

	CenterRotate(-_startTheta);

}

void OGLArc::Render()
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(rgb.red, rgb.green, rgb.blue);
		for (int i = 0; i < _size; i++)
		{
			glVertex2f(vertexs[i].X(), vertexs[i].Y());
		}
	glPopMatrix();
	glEnd();

	//Admire.
	CenterRotate(-1.0f);
}

void OGLArc::CenterRotate(float deg)
{
	OGLShape::CenterRotate(deg);
}
bool OGLArc::MouseMove(int x, int y)
{
	return true;
}
bool OGLArc::MouseLBUp(int x, int y)
{
	return true;
}
bool OGLArc::MouseLBDown(int x, int y)
{
	return true;
}