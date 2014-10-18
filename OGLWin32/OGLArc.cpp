#pragma once

#include "OGLArc.h"


OGLArc::OGLArc(Vec2 position, Color color, float startTheta, float endTheta, float radius)
:OGLShape(position, color, (int)endTheta+2, GL_TRIANGLE_FAN)
{
	_startTheta = startTheta;
	_endTheta = endTheta;
	_radius = radius;
	CreateArc();
}

void OGLArc::CreateArc()
{
	//An Arc will have it's first vertex in the center of the circle.
	vertexs[0] = _position; 
	//Vertex one will be Radius away from the first point, so we assume it's 0deg away,
	//Which is the same as moving the Y _Radius away
	for (int i = 0; i <= _endTheta; i++)
	{
		//We then repeat this process 
		vertexs[1 + i] = MathHelper<float>::Matrix2Dtransform(-(float)(_startTheta + i)) * Vec2(0, _radius);
		vertexs[1 + i] += _position;
	}

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