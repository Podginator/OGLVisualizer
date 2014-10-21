#pragma once

#include "OGLArc.h"

class OGLCircle : public OGLArc
{
public:
	OGLCircle(const Vec2f& position,const Color& color, float radius) :OGLArc(position, color, 0.f, 360.f, radius){}
	~OGLCircle();
};