#pragma once

#include "OGLLine.h"

OGLLine::OGLLine(Vec2 position, Color color, Vec2 endPos) :_endPosition(endPos), OGLShape(position, color, 3, GL_LINES)
{
	vertexs[0] = _position;
	vertexs[1] = _endPosition;
}

OGLLine::OGLLine(Vec2 position, std::string hexcolor, Vec2 endPos) :_endPosition(endPos), OGLShape(position, hexcolor, 3, GL_LINES)
{
	vertexs[0] = _position;
	vertexs[1] = _endPosition;
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
