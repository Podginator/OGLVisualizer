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
	vertexs[1] = MathHelper<float>::Matrix2Dtransform((-_startTheta)) * Vec2(0, _radius);
	vertexs[1] += _position;

	for (int i = 0; i <= _endTheta; i++)
	{
		vertexs[2 + i] = MathHelper<float>::Matrix2Dtransform(-(float)(_startTheta + i)) * Vec2(0, _radius);
		vertexs[2 + i] += _position;
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