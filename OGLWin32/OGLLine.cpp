#pragma once

#include "OGLLine.h"

OGLLine::OGLLine(Vec2f position, Color color, Vec2f endPos) :_endPosition(endPos), OGLShape(position, color, 3, GL_LINES)
{
	vertexs[0] = _position;
	vertexs[1] = _endPosition;
}

OGLLine::OGLLine(Vec2f position, std::string hexcolor, Vec2f endPos) :_endPosition(endPos), OGLShape(position, hexcolor, 3, GL_LINES)
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
