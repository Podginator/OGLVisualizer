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
	vertexs[0] = _position;
	vertexs[1] = Vec2(_position.X(), _position.Y() + _radius);
	for (int i = 0; i <= _endTheta; i++)
	{
		vertexs[2+i] = MathHelper<float>::Matrix2Dtransform(-(float)i) * vertexs[1];
	}
}

void OGLArc::Render()
{
	glBegin(GL_TRIANGLE_FAN);
		RenderVertexs();
	glEnd();
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