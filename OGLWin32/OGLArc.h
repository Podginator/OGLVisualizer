#pragma once

#include "OGLShape.h"

class OGLArc : public OGLShape
{
public:
	OGLArc(Vec2 position, Color color, float startTheta, float endTheta, float radius);
	OGLArc(Vec2 position, std::string hexColor, float startTheta, float endTheta, float radius);
	~OGLArc();

	void			Render();
	bool			MouseMove(int x, int y);
	bool			MouseLBUp(int x, int y);
	bool			MouseLBDown(int x, int y);

protected:
	float _startTheta;
	float _endTheta;
	float _radius;
	void CreateArc();



};