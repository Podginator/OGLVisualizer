#pragma once

#include "OGLShape.h"

class OGLLine : public OGLShape
{
protected:
	Vec2f _endPosition;
public:
	OGLLine(Vec2f position, Color color, Vec2f endPos);
	OGLLine(Vec2f position, std::string hexColor, Vec2f endPos);
	~OGLLine();

	bool			MouseMove(int x, int y);
	bool			MouseLBUp(int x, int y);
	bool			MouseLBDown(int x, int y);
};
