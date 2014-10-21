#pragma once

#include "OGLArc.h"

class OGLCircle : public OGLArc
{
public:
	OGLCircle(Vec2f position, Color color, float radius) :OGLArc(position, color, 0.f, 360.f, radius){}
	~OGLCircle();
};