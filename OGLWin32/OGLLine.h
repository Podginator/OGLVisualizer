#pragma once

#include "OGLShape.h"

class OGLLine : public OGLShape
{
protected:
	Vec2 _endPosition;
public:
	OGLLine(Vec2 position, Color color, Vec2 endPos);
	OGLLine(Vec2 position, std::string hexColor, Vec2 endPos);
	~OGLLine();

	void			Render();
	bool			MouseMove(int x, int y);
	bool			MouseLBUp(int x, int y);
	bool			MouseLBDown(int x, int y);
};
