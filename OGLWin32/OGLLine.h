#pragma once

#include "OGLShape.h"

class OGLLine : public OGLShape
{
protected:
	Vec2 _endPosition;
public:
	OGLLine(Vec2 position, Color color, Vec2 endPos) :_endPosition(endPos), OGLShape(position, color, 2){};
	OGLLine(Vec2 position, std::string hexColor, Vec2 endPos) :_endPosition(endPos), OGLShape(position, hexColor, 2){};
	~OGLLine();

	void			Render();
	bool			MouseMove(int x, int y);
	bool			MouseLBUp(int x, int y);
	bool			MouseLBDown(int x, int y);
};
