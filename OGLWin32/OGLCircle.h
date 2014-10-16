#pragma once

#include "OGLArc.h"

class OGLCircle : public OGLArc
{
public:
	OGLCircle(Vec2 position, Color color, float radius) :OGLArc(position, color, 0.f, 360.f, radius){}
	OGLCircle(Vec2 position, std::string hexColor, float radius) :OGLArc(position, hexColor, 0.f, 360.f, radius){};
	~OGLCircle();
};