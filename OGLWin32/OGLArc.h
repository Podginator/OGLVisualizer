#pragma once

#include "OGLShape.h"

class OGLArc : public OGLShape
{
public:
	OGLArc(Vec2f position, Color color, float startTheta, float endTheta, float radius);
	OGLArc(Vec2f position, std::string hexColor, float startTheta, float endTheta, float radius);
	~OGLArc();

	bool			MouseMove(int x, int y);
	bool			MouseLBUp(int x, int y);
	bool			MouseLBDown(int x, int y);

protected:
	float _startTheta;
	float _endTheta;
	float _radius;
	void CreateArc();



};