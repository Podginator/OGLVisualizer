#pragma once

#include "OGLShape.h"

class OGLArc : public OGLShape
{
public:
	OGLArc(const Vec2f& position,const Color& color, float startTheta, float endTheta, float radius);
	~OGLArc();


	bool MouseMove(int x, int y);
	bool MouseLBUp(int x, int y);
	bool MouseLBDown(int x, int y);

protected:
	bool MouseInside(int x, int y);
	float _startTheta;
	float _endTheta;
	float _radius;
	void CreateArc();
};