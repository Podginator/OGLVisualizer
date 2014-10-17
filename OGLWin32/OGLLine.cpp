#pragma once

#include "OGLLine.h"

OGLLine::OGLLine(Vec2 position, Color color, Vec2 endPos) :_endPosition(endPos), OGLShape(position, color, 3)
{
	vertexs[0] = _position;
	vertexs[1] = _endPosition;
}

OGLLine::OGLLine(Vec2 position, std::string hexcolor, Vec2 endPos) :_endPosition(endPos), OGLShape(position, hexcolor, 3)
{
	vertexs[0] = _position;
	vertexs[1] = _endPosition;
}

void OGLLine::Render()
{

	glBegin(GL_LINES);
	RenderVertexs();
	glEnd();
}

bool OGLLine::MouseMove(int x, int y)
{
	return true;
}
bool OGLLine::MouseLBUp(int x, int y)
{
	return true;
}
bool OGLLine::MouseLBDown(int x, int y)
{
	CenterRotate(1.0f);
	return true;
}
