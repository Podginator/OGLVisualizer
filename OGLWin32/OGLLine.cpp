#pragma once

#include "OGLLine.h"

void OGLLine::Render()
{
	glBegin(GL_LINE);
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
